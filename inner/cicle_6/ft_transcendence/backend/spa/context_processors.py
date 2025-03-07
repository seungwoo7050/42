# NOTE: <ijo> This code may replace
#   index/templatetags/render_vite_bundle.py in the future.
# Currently on ice.


# from django.conf import settings

# def reactjs_assets_paths(request):
#     staticfiles_base = settings.STATICFILES_DIRS[0]
#     build_files = settings.VITE_BUILD_DIR
#     return {
#         "reactjs_assets_js_paths":[str(x.relative_to(staticfiles_base)) for x in build_files.glob("*.js")],
#         "reactjs_assets_css_paths":[str(x.relative_to(staticfiles_base)) for x in build_files.glob("*.css")],
#     }
