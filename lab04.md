---
layout: default
title: 数据加密与编码
---

# 数据加密与编码

数据加密指通过加密算法和加密密钥将明文转变为密文。大数据时代，信息安全显得尤为重要。今天，让我们一起了解数据加密与编码的相关知识，保护个人隐私。

## 数据加密术语

1.明文，即原始的或未加密的数据。通过加密算法对其进行加密，加密算法的输入信息为明文和密钥。

2.密文，明文加密后的格式，是加密算法的输出信息。加密算法是公开的，而密钥则是不公开的。密文不应为无密钥的用户理解，用于数据的存储以及传输。

3.密钥，是由数字、字母或特殊符号组成的字符串，用它控制数据加密、解密的过程。

4.加密，把明文转换为密文的过程。

5.加密算法，加密所采用的变换方法。

6.解密，对密文实施与加密相逆的变换，从而获得明文的过程。

7.解密算法，解密所采用的变换方法。

## 数据加密原理及举例

原理：发送方通过加密设备或加密算法，用加密密钥将数据加密后发送出去。接收方在收到密文后，用解密密钥将密文解密，恢复为明文。

举例：

明文为字符串：
AS KINGFISHERS CATCH FIRE
（为简便起见，假定所处理的数据字符仅为大写字母和空格符）。

假定密钥为字符串：ELIOT

加密算法为：
1) 将明文划分成多个密钥字符串长度大小的块（空格符以"+"表示）
AS+KI NGFIS HERS+ CATCH +FIRE
2) 用0~26范围的整数取代明文的每个字符，空格符=00，A=01，...，Z=26：
3) 与步骤2一样对密钥的每个字符进行取代：
0512091520
4) 对明文的每个块，将其每个字符用对应的整数编码与密钥中相应位置的字符的整数编码的和模27后的值（整数编码）取代：
举例：第一个整数编码为 (01+05)%27=06
5) 将步骤4的结果中的整数编码再用其等价字符替换：
FDIZB SSOXL MQ+GT HMBRA ERRFY

## 数据加密标准（DES）

将明文分割成许多64位大小的块，每个块用64位密钥进行加密，实际上，密钥由56位数据位和8位奇偶校验位组成，因此只有56个可能的密码而不是64个。每块先用初始置换方法进行加密，再连续进行16次复杂的替换，最后再对其施用初始置换的逆。第i步的替换并不是直接利用原始的密钥K，而是由K与i计算出的密钥Ki。

## 加密技术

### 对称加密技术原理应用

```c
DESCryptoServiceProvider
RC2CryptoServiceProvider
RijndaelManaged
TripleDESCryptoServiceProvider
//例加密文本文件(RijndaelManaged )
byte[] key = { 24, 55, 102,24, 98, 26, 67, 29, 84, 19, 37, 118, 104, 85, 121, 27, 93, 86, 24, 55, 102, 24,98, 26, 67, 29, 9, 2, 49, 69, 73, 92 };
byte[] IV ={ 22, 56, 82, 77, 84, 31, 74, 24,55, 102, 24, 98, 26, 67, 29, 99 };
RijndaelManaged myRijndael = new RijndaelManaged();
FileStream fsOut = File.Open(strOutName, FileMode.Create,FileAccess.Write);//strOutName文件名及路径 FileStream fsIn = File.Open(strPath, FileMode.Open,FileAccess.Read);
CryptoStream csDecrypt=new CryptoStream(fsOut,myRijndael.CreateEncryptor(key,IV),CryptoStreamMode.Write);//读加密文本
BinaryReader br = new BinaryReader(fsIn);
csDecrypt.Write(br.ReadBytes((int)fsIn.Length),0, (int)fsIn.Length);
csDecrypt.FlushFinalBlock();
csDecrypt.Close();
fsIn.Close();
fsOut.Close();
//解密文件
byte[] key = { 24, 55, 102, 24, 98, 26, 67, 29, 84, 19, 37, 118,104, 85, 121, 27, 93, 86, 24, 55, 102, 24, 98, 26, 67, 29, 9, 2, 49, 69, 73, 92};
byte[] IV ={ 22, 56, 82, 77, 84, 31, 74, 24, 55, 102, 24, 98, 26,67, 29, 99 };
RijndaelManaged myRijndael = new RijndaelManaged();
FileStream fsOut = File.Open(strPath, FileMode.Open, FileAccess.Read);
CryptoStream csDecrypt = new CryptoStream(fsOut, myRijndael.CreateDecryptor(key,IV), CryptoStreamMode.Read);
StreamReader sr = new StreamReader(csDecrypt);//把文件读出来
StreamWriter sw = new StreamWriter(strInName);//解密后文件写入一个新的文件
sw.Write(sr.ReadToEnd());
sw.Flush();
sw.Close();
sr.Close();f
sOut.Close();
用图片加密(RC2CryptoServiceProvider )
FileStreamfsPic = new FileStream(pictureBox1.ImageLocation,FileMode.Open, FileAccess.Read);
//加密文件流（textBox1.Text是文件名及路径）
FileStream fsText = new FileStream(textBox1.Text, FileMode.Open,FileAccess.Read);
byte[] bykey = new byte[16]; //初始化
Key IVbyte[] byIv = new byte[8];
fsPic.Read(bykey, 0, 16);
fsPic.Read(byIv, 0, 8);
RC2CryptoServiceProvider desc = newRC2CryptoServiceProvider();//desc进行加密
BinaryReader br = new BinaryReader(fsText);//从要加密的文件中读出文件内容
FileStream fsOut = File.Open(strLinPath,FileMode.Create, FileAccess.Write); // strLinPath临时加密文件路径CryptoStream cs = new CryptoStream(fsOut, desc.CreateEncryptor(bykey,byIv), CryptoStreamMode.Write);//写入临时加密文件
cs.Write(br.ReadBytes((int)fsText.Length),0, (int)fsText.Length);//写入加密流
cs.FlushFinalBlock();
cs.Flush();
cs.Close();
fsPic.Close();
fsText.Close();
fsOut.Close();
用图片解密
FileStream fsPic = new FileStream(pictureBox1.ImageLocation, FileMode.Open, FileAccess.Read); //图片流FileStream fsOut = File.Open(textBox1.Text,FileMode.Open, FileAccess.Read);//解密文件流
byte[] bykey = new byte[16]; //初始化
Key IVbyte[] byIv = new byte[8];
fsPic.Read(bykey, 0, 16);
fsPic.Read(byIv, 0, 8);
string strPath = textBox1.Text;//加密文件的路径
int intLent = strPath.LastIndexOf("\\")+ 1;
int intLong = strPath.Length;
string strName = strPath.Substring(intLent, intLong - intLent);//要加密的文件名称
string strLinPath = "C:\\"+ strName;//临时解密文件路径
FileStream fs = new FileStream(strLinPath, FileMode.Create,FileAccess.Write);
RC2CryptoServiceProvider desc = newRC2CryptoServiceProvider();//desc进行解密
CryptoStream csDecrypt = new CryptoStream(fsOut, desc.CreateDecryptor(bykey,byIv), CryptoStreamMode.Read);
//读出加密文件
BinaryReader sr = new BinaryReader(csDecrypt);//从要加密流中读出文件内容
BinaryWriter sw = new BinaryWriter(fs);//写入解密流
sw.Write(sr.ReadBytes(Convert.ToInt32(fsOut.Length)));
//sw.Flush();
sw.Close();
sr.Close();
fs.Close();
fsOut.Close();
fsPic.Close();
csDecrypt.Flush();
File.Delete(textBox1.Text.TrimEnd());//删除原文件
File.Copy(strLinPath, textBox1.Text);//复制加密文件
File.Delete(strLinPath);//删除临时文件
```

### 非对称加密技术

#### 原理

1.A要向B发送信息，A和B都要产生一对用于加密非对称加密算法和解密的公钥和私钥。

2.A的私钥保密，A的公钥告诉B；B的私钥保密，B的公钥告诉A。

3.A要给B发送信息时，A用B的公钥加密信息，因为A知道B的公钥。

4.A将这个消息发给B（已经用B的公钥加密消息）。

5.B收到这个消息后，B用自己的私钥解密A的消息。其他所有收到这个报文的人都无法解密，因为只有B才有B的私钥。

#### 应用

```c
DSACryptoServiceProvider
 
非对称加密算法 
RSACryptoServiceProvider
//加密
UnicodeEncoding encoding = new UnicodeEncoding();
byte[] PasswordBytes = encoding.GetBytes(password);//将密码转换为字节数组RSACryptoServiceProvider crypt=new RSACryptoServiceProvider();//RSA加密算法，非对称PasswordBytes=crypt.Encrypt(password ,false);//加密字节数组，这是加密后的密码值，放入数据库中的表字段中。
string key=crypt.ToXmlString(true);//输出密钥为XML格式的字符串，且包含私钥，这个字符串要作为数据库表中的一个字段同用户的密码放在一起。
//解密
RSACryptoServiceProvider crypt=new RSACryptoServiceProvider();//已随机生成了一个密钥对
crypt.Clear();//毁掉当前密钥对
crypt.FromXmlString(key)//输入密钥对，key是从数据库表字段中读取的那个XML格式的字符串，即密钥字段PasswordBytes=crypt.Decrypt(password ,false);//解密字节数组，返回原始密码给用户
```

**也许现在你并不能完全理解和掌握数据加密的应用方法，但你需要知道它的原理，来进行简单的数据加密，在重要的文件中适当应用，以保护个人隐私。**
