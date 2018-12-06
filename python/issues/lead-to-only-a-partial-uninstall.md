### description
```
%pip install pyldap>=2.4.15
  Failed building wheel for python-ldap
Cannot uninstall 'python-ldap'. It is a distutils installed project and thus we cannot accurately determine which files belong to it which would lead to only a partial uninstall.

```

---


### 方法一
```
I used follow steps and resolved this problem:

Reduced version,
pip install --upgrade --force-reinstall pip==9.0.3
Tried to re-install package
pip install xxx --disable-pip-version-check
At last, recover the latest version for pip
pip install --upgrade pip
```

### 方法二
```
In the orignal case above, that'd be:

pip install docker-py --ignore-installed PyYAML
```
### link
https://github.com/pypa/pip/issues/5247
