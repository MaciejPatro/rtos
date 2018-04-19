
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
cmake -D $2 $repo_dir
