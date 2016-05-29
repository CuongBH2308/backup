"""
WSGI config for mysite project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/1.6/howto/deployment/wsgi/
"""

import os
import sys

# FIXME: although polls has been installed using pip, and could be imported in a
# interactive shell, it failed when running from httpd mod_wsgi
# add this hardcoded path to make sure polls package could be imported
sys.path.append("C:\\Users\\baiyanh\\AppData\\Roaming\\Python\\Python27\\site-packages")
import polls
sys.path.append(os.path.dirname(__file__))
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "mysite.settings")

from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()
