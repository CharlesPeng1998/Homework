#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
using namespace std;

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：此函数允许放到 common_cfgfile_tools.cpp 中做为内部工具函数
***************************************************************************/
static int file_length(fstream &fp)
{
	int file_len, now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fp.seekg(0, ios::end);
	file_len = int(fp.tellp());

	/* 指针移动回函数调用前的原位置 */
	fp.seekg(now_pos, ios::beg);

	return file_len;
}

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：此函数允许放到 common_cfgfile_tools.cpp 中做为内部工具函数
***************************************************************************/
static int file_resize(const char *filename, fstream &fp, int newsize)
{
	int now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	experimental::filesystem::resize_file(filename, newsize);

	/* 如果当前文件指针超过了文件大小，则回到文件头 */
	if (now_pos > newsize)
		fp.seekg(0, ios::beg);

	return 0;
}

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：
***************************************************************************/
int main()
{
	const char *fname = "test.txt";
	fstream fp;
	char buf[80];

	/* 首先建立test.txt，并向其中写入测试内容 */
	fp.open(fname, ios::out);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}

	fp << "窗前明月光，" << endl;
	fp << "疑是地上霜。" << endl;
	fp << "举头望明月，" << endl;
	fp << "低头思故乡。" << endl;

	fp.close();

	cout << "请在文件夹中观察test.txt的长度是否56字节，并用第三方编辑(UltraEdit等)软件打开test.txt查看" << endl;
	cout << "按C继续" << endl;
	while (_getch() != 'C')
		;

	/* 文件以读写方式打开（不存在则失败）*/
	fp.open(fname, ios::in | ios::out);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}

	cout << "文件长度" << file_length(fp) << "字节" << endl;

	// 使文件在原基础上缩减10字节
	file_resize(fname, fp, file_length(fp) - 10);

	cout << "文件新长度" << file_length(fp) << "字节" << endl;

	cout << "请输入一个字符串(11-50字符之间)" << endl;
	gets_s(buf);

	/* 用输入字符串的内容将文件的第二行前10字节(五个汉字)替换掉 */
	fp.seekg(14, ios::beg);
	buf[10] = '\0'; //只写前10字节，如果输入不满10字节，会有乱码
	fp << buf;
	fp.close();
	/* 执行到此，测试完成 */

	cout << "请在文件夹中观察test.txt的长度是否46字节，并用第三方编辑(UltraEdit等)软件打开test.txt查看" << endl;
	cout << "按C继续" << endl;
	while (_getch() != 'C')
		;

	/* 再次读取文件长度 */
	fp.open(fname, ios::in);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}
	cout << "关闭后再次验证新文件长度" << file_length(fp) << "字节" << endl;
	fp.close();

	return 0;
}
