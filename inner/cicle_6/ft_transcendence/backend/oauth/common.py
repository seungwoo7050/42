from django.core.exceptions import ValidationError

def validate_displayname(value: str) -> bool:
    """
    닉네임 유효성 검사
    Returns: 
        bool: 유효하면 True, 아니면 ValidationError 발생
    """
    if not value.isalnum():
        raise ValidationError('닉네임은 영문자와 숫자만 사용할 수 있습니다.')
    
    forbidden_names = ['ai', 'admin', 'me']
    if value.lower() in forbidden_names:
        raise ValidationError('사용할 수 없는 닉네임입니다.')
    
    return True