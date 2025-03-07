# # This template tag is needed for production
# # Add it to one of your django apps (/appdir/templatetags/render_vite_bundle.py, for example)

# import os
# import json

# from django import template
# from django.conf import settings
# from django.utils.safestring import mark_safe

# register = template.Library()


# @register.simple_tag
# def render_vite_bundle():
#     """
#     Template tag to render a vite bundle.
#     Supposed to only be used in production.
#     For development, see other files.
#     """
  
#     try:
#         manifest_path = os.path.join(settings.STATIC_ROOT, ".vite", "manifest.json")
#         print(f"[DEBUG] Checking manifest path: {manifest_path}")
#         with open(manifest_path, "r") as fd:
#             manifest = json.load(fd)
#     except FileNotFoundError:
#         raise Exception(f"Manifest file not found: {manifest_path}")
#     except json.JSONDecodeError:
#         raise Exception(f"Invalid JSON in manifest file: {manifest_path}")



#     # imports_files = "".join(
#     #     [
#     #         f'<script type="module" src="/static/{manifest[file]["file"]}"></script>'
#     #         for file in manifest["index.html"]["imports"]
#     #     ]
#     # )

#     # print(imports_files)

#     return mark_safe(
#         f"""<script type="module" src="/static/{manifest['index.html']['file']}"></script>
#         <link rel="stylesheet" type="text/css" href="/static/{manifest['index.html']['css'][0]}" />"""
#     )

#         # {imports_files}"""


# This template tag is needed for production
# Add it to one of your django apps (/appdir/templatetags/render_vite_bundle.py, for example)

import os
import json

from django import template
from django.conf import settings
from django.utils.safestring import mark_safe

register = template.Library()


@register.simple_tag
def render_vite_bundle():
    """
    Template tag to render a vite bundle.
    Supposed to only be used in production.
    For development, see other files.
    """
  
    try:
        fd = open(f"{settings.VITE_APP_DIR}/dist/.vite/manifest.json", "r")
        manifest = json.load(fd)
    except:
        raise Exception(
            f"Vite manifest file not found or invalid. Maybe your {settings.VITE_APP_DIR}/dist/.vite/manifest.json file is empty?"
        )

    # imports_files = "".join(
    #     [
    #         f'<script type="module" src="/static/{manifest[file]["file"]}"></script>'
    #         for file in manifest["index.html"]["imports"]
    #     ]
    # )

    # print(imports_files)

    return mark_safe(
        f"""<script type="module" src="/static/{manifest['index.html']['file']}"></script>
        <link rel="stylesheet" type="text/css" href="/static/{manifest['index.html']['css'][0]}" />"""
    )

        # {imports_files}"""