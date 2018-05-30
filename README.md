# KPortScanner
一个在Linux终端上运行端口扫描程序

## 编译
安装构建套件，以Ubuntu为例:
```
sudo apt-get install build-essential
```
进入项目文件，然后进入cmd文件夹:
```
cd ./cmd
```
运行编译脚本
```
./build.sh
```
如果构建不成功，你也可以尝试自己使用gcc编译:
```
gcc ./scanner.c -o ./scanner
```
更改执行权限:
```
chmod 777 ./scanner
```

## 运行
```
./scanner ip portStart portEnd threadNum
```
参数说明:
* ip: 被扫描者的ip地址
* portStart: 起始端口
* portEnd: 结束端口
* threadNum: 线程数
