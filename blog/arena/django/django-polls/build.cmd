pip uninstall django-polls
python setup.py sdist
pip install --user dist\django-polls-0.1.zip
rmdir /s/q dist django_polls.egg-info