```
Command "/usr/bin/python -u -c "import setuptools, tokenize;__file__='/tmp/pip-install-BQIEv9/python-ldap/setup.py';f=getattr(tokenize, 'open', open)(__file__);code=f.read().replace('\r\n', '\n');f.close();exec(compile(code, __file__, 'exec'))" install --record /tmp/pip-record-Jp5v5O/install-record.txt --single-version-externally-managed --compile" 
failed with error code 1 in /tmp/pip-install-BQIEv9/python-ldap/

```

原因是缺少相应的devel库.


```
sudo yum install python-devel openldap-devel

```
