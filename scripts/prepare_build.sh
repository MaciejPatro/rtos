
repo_dir=$(pwd)
cd ..
if [ ! -d "embedded_build" ]; then
    mkdir embedded_build
fi
cd embedded_build
if [ ! -d $1 ]; then
    mkdir $1
fi
cd $1

shift
command_options=""

while test ${#} -gt 0
do
  command_options="$command_options -D $1"
  shift
done

cmake $command_options $repo_dir
