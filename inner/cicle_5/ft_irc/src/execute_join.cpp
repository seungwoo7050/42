#include "inc/Executor.hpp"

#include "inc/Connection.hpp"
#include "inc/Server.hpp"
#include "inc/Message.hpp"
#include "inc/macros.hpp"

#include "inc/Parser.hpp"

#include "inc/debug.hpp"
#include "inc/utils.hpp"


/*
    Command: JOIN
    Parameters: <channel>{,<channel>} [<key>{,<key>}]
    Alt Params: 0
*/
void Executor::_execute_join(Server &server, Connection *&node, const Message &msg)
{
    if (!node->is_registered)   // only registered user can request join
    {
        dispatch_packet(server, node, BUILD_ERR_NOTREGISTERED(server.servername, node->nickname));
        return;
    }
    else if (msg.params.size() != 1 && msg.params.size() != 2)
    {
        dispatch_packet(server, node, BUILD_ERR_NEEDMOREPARAMS(server.servername, msg.command));
        return;
    }

    std::string rpl;

    if (msg.params.at(0) == "0")    // JOIN 0
    {
        std::size_t i = 0;
        std::size_t n = node->chandb.size();
        while (i < n)
        {
            std::map<std::string, Channel *>::iterator beg = node->chandb.begin();
            Channel *chan = beg->second;

            // broadcast PART reply
            Executor::broadcast(server, chan, ":" + node->nickname + " PART " + chan->name + " \r\n");

            // part channel
            node->chandb.erase(beg);
    
            // channel cleans up db
            chan->part(node);
            if (chan->clientdb.empty())	// clean up server resources if chan has been made empty
            {
                std::map<std::string, std::list<Channel *>::iterator>::iterator find = server.chandb.find(chan->name);
                server.chans.erase(find->second);
                server.chandb.erase(find);
                delete chan; // delete empty chan
            }

            ++i;
        }

        return;
    }

    std::vector<std::string> channels;
    Parser::tokenize(msg.params.at(0), ",", channels);


    std::vector<std::string> keys;
    if (msg.params.size() == 2)
        Parser::tokenize(msg.params.at(1), ",", keys);

    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        Parser::tolower(*it);
        if (Parser::is_channel(*it) == false)
        {
            rpl += BUILD_ERR_NOSUCHCHANNEL(server.servername, node->nickname, *it);
            continue;
        }

        std::map<std::string, std::list<Channel *>::iterator>::iterator find = server.chandb.find(*it);
        if (find == server.chandb.end())
        {
            if (node->chandb.size() == 10)
            {
                rpl += BUILD_ERR_TOOMANYCHANNELS(server.servername, node->nickname, *it);
                continue;
            }

            Channel *chan = new Channel(*it, node);
            server.chans.push_front(chan);
            server.chandb.insert(std::pair<std::string, std::list<Channel *>::iterator>(*it, server.chans.begin()));
            chan->clientdb.insert(std::pair<int, Connection *>(node->sockfd, node));
            node->chandb.insert(std::pair<std::string, Channel *>(*it, chan));
        }
        else
        {
            Channel *chan = *find->second;

            if (chan->clientdb.find(node->sockfd) != chan->clientdb.end())
            {
                rpl += BUILD_ERR_USERONCHANNEL(server.servername, node->nickname, *it);
                continue;
            }

            if (node->chandb.size() == 10)
            {
                rpl += BUILD_ERR_TOOMANYCHANNELS(server.servername, node->nickname, *it);
                continue;
            }

            if (chan->rdstate() & Channel::kbit)
            {
                std::ptrdiff_t dist = std::distance(channels.begin(), it);

                if (dist > 0 && static_cast<std::size_t>(dist) < keys.size())
                {
                    if (keys.at(dist) != chan->key)
                    {
                        rpl += BUILD_ERR_BADCHANNELKEY(server.servername, node->nickname, *it);
                        continue;
                    }
                }
                else
                {
                    rpl += BUILD_ERR_BADCHANNELKEY(server.servername, node->nickname, *it);
                    continue;
                }
            }

            if (chan->rdstate() & Channel::lbit && chan->clientdb.size() == chan->limit)
            {
                rpl += BUILD_ERR_CHANNELISFULL(server.servername, node->nickname, *it);
                continue;
            }

            if (chan->rdstate() & Channel::ibit)
            {
                std::map<int, Connection *>::iterator find = chan->invitedb.find(node->sockfd);
                if (find == chan->invitedb.end())
                {
                    rpl += BUILD_ERR_INVITEONLYCHAN(server.servername, node->nickname, *it);
                    continue;
                }
                else
                {
                    chan->invitedb.erase(node->sockfd);
                }
            }

            chan->clientdb.insert(std::pair<int, Connection *>(node->sockfd, node));
            node->chandb.insert(std::pair<std::string, Channel *>(*it, chan));

            rpl += ":" + node->nickname + " JOIN " + *it + " \r\n";
            if ((chan->rdstate() & Channel::tbit) && !chan->topic.empty()) 
            {
                rpl += BUILD_RPL_TOPIC(server.servername, node->nickname, *it, chan->topic);
                rpl += BUILD_RPL_TOPICWHOTIME(server.servername, node->nickname, *it, chan->topic_setter, utils::time_to_str(chan->topic_time));
            }
            rpl += _generate_rpl_namreply(server.servername, chan, node);
            rpl += BUILD_RPL_ENDOFNAMES(server.servername, node->nickname, *it);
        }
    }
    dispatch_packet(server, node, rpl);
}

void Executor::_execute_part(Server &server, Connection *&node, const Message &msg)
{
    if (msg.params.size() != 1 && msg.params.size() != 2)
    {
		dispatch_packet(server, node, BUILD_ERR_NEEDMOREPARAMS(server.servername, msg.command));
        return;
    }

    std::string channame = msg.params[0];
	Parser::tolower(channame);
    std::string reason = msg.params[1];

    // 채널이 서버에 존재하는지 확인
	if (server.chandb.find(channame) == server.chandb.end())
	{
		dispatch_packet(server, node, BUILD_ERR_NOSUCHCHANNEL(server.servername, node->nickname, channame));
		return;
	}

    // check if node is party to the channel
	std::map<std::string, Channel *>::iterator chanit = node->chandb.find(channame);
	if (chanit == node->chandb.end())
	{
		dispatch_packet(server, node, BUILD_ERR_NOTONCHANNEL(server.servername, node->nickname, channame));
		return;
	}

    Channel *chan = chanit->second;

    // broadcast PART reply
    Executor::broadcast(server, chan, ":" + node->nickname + " PART " + channame + " :" + reason + "\r\n");

    // part channel
    node->chandb.erase(chanit);
    
    // channel cleans up db
	chan->part(node);
	if (chan->clientdb.empty())	// clean up server resources if chan has been made empty
	{
		std::map<std::string, std::list<Channel *>::iterator>::iterator find = server.chandb.find(chan->name);
		server.chans.erase(find->second);
		server.chandb.erase(find);
		delete chan; // delete empty chan
	}
}

std::string Executor::_generate_rpl_namreply(const std::string &servname, Channel *&chan, Connection *&node)
{
    std::string ret = ":" + servname + " 353 " + node->nickname + " = " + chan->name + " :";
    for (std::map<int, Connection *>::iterator it = chan->clientdb.begin(); it != chan->clientdb.end(); ++it)
    {
        Connection *client = it->second;
        if (chan->privdb.find(client) != chan->privdb.end())
            ret += "@";
        ret += client->nickname + " ";
    }
    ret += "\r\n";

    return ret;
}
