project.mdproject2
###软件环境：Visual Studio 2019 
硬件环境：Intel(R) Core(TM) i5-10210U CPU @ 1.60GHz 2.11 GHz 
代码实现思路： 
sm4的ρ攻击目的与生日攻击相似，寻求基于sm4哈希值的弱碰撞（如果给定一个消息M1，寻找消息M2，使得用hash函数加密后的值h(M1)=h(M2)，则说明存在弱碰撞），
而使用pollard rho算法则是通过rho递推表达式依次尝试寻找出h(M1)=h(M2)，在代码中使用了类似于查表攻击的结构，一边存储前16bit可能的消息哈希值，一边查找
是否有和已有的哈希值重复的值；
若有，则说明该攻击算法成功，实验结果为某消息的前16bit哈希值的攻击。 
###运行结果 
攻击消息前16bit哈希值所用时间大约为242s 
结果如下： 
![){AZE0 H`6@HCN()`(SEGVK](https://github.com/Miraitowa7/homework-group10/assets/129491822/571479d6-035e-4903-9926-3e1521007dd5)
