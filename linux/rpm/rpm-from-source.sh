# How to create an RPM from source with spec file

# This is for Redhat versions of linux. Sometimes when you search for an rpm package,
# it is either outdated or not available. The only thing available is the source code.
# You can create a custom RPM package from source.
#
# For this example, I'll be using the latest version of Git, currently v.1.7.7.3

# Step: 1
# Install rpmbuild

yum install -y rpm-build

# Step: 2
# Create rpmbuild folders in your home directory

mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

# Step: 3
# Download the source file
#
# Source files are usually available in tar.gz or tar.bz2 format. Create a src folder
# in your home directory to store your files, download the file, uncompress it and
# move the compressed file to the rpm build SOURCES directory

mkdir -p ~/src && cd ~/src
wget http://git-core.googlecode.com/files/git-1.7.7.3.tar.gz
tar -xzvf git-1.7.7.3.tar.gz
mv git-1.7.7.3.tar.gz ~/rpmbuild/SOURCES

# Step: 4
# Locate .spec file and build rpm
#
# If you get any errors during build, it is usually because of dependencies. Simply
# install the dependencies with `yum install [dependency]` and run rpmbuild again.

cd ~/src/git-1.7.7.3 && ls | grep *.spec
rpmbuild -ba git.spec
