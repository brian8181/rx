git ls-tree -l HEAD -- /home/brian/src/rx/configure.ac
git cat-file -s 9dd1c8e21f2ee5fde112292e785f4826a324de15

git show --textconv HEAD:configure.ac
git show --textconv :configure.ac 

git status -z -u

git for-each-ref "--format=%(refname)%00%(upstream:short)%00%(upstream:track)%00%(objectname) refs/heads/master refs/remotes/master"
git for-each-ref "--sort -committerdate --format %(refname) %(objectname) %(*objectname)"

git remote --verbose
git config --get commit.template
