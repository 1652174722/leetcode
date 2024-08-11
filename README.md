# 初始化git 
git config --global user.name "yiqiangrexue"

git config --global user.email "1652174722@qq.com"

# 并行编译
make clean && make -j $(cat /proc/cpuinfo  |grep processor | wc -l) && make run
