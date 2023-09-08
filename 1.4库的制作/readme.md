# 库的制作
## 1.静态库的制作
1. `gcc *.c -c *.o`
2. `ar -rcs libtest.a dog.o hello.o test.o（或者*.o）`（参数格式必须按照顺序）
    - r: 将文件插入备存文件中
    - c: 建立备存文件
    - s: 索引

## 2.静态库的使用

