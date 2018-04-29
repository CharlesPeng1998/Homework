#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
using namespace std;

/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    �����˺�������ŵ� common_cfgfile_tools.cpp ����Ϊ�ڲ����ߺ���
***************************************************************************/
static int file_length(fstream &fp)
{
	int file_len, now_pos;

	/* ��ǰΪ����״̬�򷵻�-1 */
	if (fp.fail())
		return -1;

	/* ȡfp��ǰָ��λ�� */
	now_pos = int(fp.tellg());

	/* ���ļ�ָ���ƶ�����󣬴�ʱtellp�Ľ�������ļ���С */
	fp.seekg(0, ios::end);
	file_len = int(fp.tellp());

	/* ָ���ƶ��غ�������ǰ��ԭλ�� */
	fp.seekg(now_pos, ios::beg);

	return file_len;
}

/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    �����˺�������ŵ� common_cfgfile_tools.cpp ����Ϊ�ڲ����ߺ���
***************************************************************************/
static int file_resize(const char *filename, fstream &fp, int newsize)
{
	int now_pos;

	/* ��ǰΪ����״̬�򷵻�-1 */
	if (fp.fail())
		return -1;

	/* ȡfp��ǰָ��λ�� */
	now_pos = int(fp.tellg());

	/* �����С�Ǹ�����ֱ�ӷ���-1 */
	if (newsize < 0)
		return -1;

	experimental::filesystem::resize_file(filename, newsize);

	/* �����ǰ�ļ�ָ�볬�����ļ���С����ص��ļ�ͷ */
	if (now_pos > newsize)
		fp.seekg(0, ios::beg);

	return 0;
}

/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    ����
***************************************************************************/
int main()
{
	const char *fname = "test.txt";
	fstream fp;
	char buf[80];

	/* ���Ƚ���test.txt����������д��������� */
	fp.open(fname, ios::out);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}

	fp << "��ǰ���¹⣬" << endl;
	fp << "���ǵ���˪��" << endl;
	fp << "��ͷ�����£�" << endl;
	fp << "��ͷ˼���硣" << endl;

	fp.close();

	cout << "�����ļ����й۲�test.txt�ĳ����Ƿ�56�ֽڣ����õ������༭(UltraEdit��)�����test.txt�鿴" << endl;
	cout << "��C����" << endl;
	while (_getch() != 'C')
		;

	/* �ļ��Զ�д��ʽ�򿪣���������ʧ�ܣ�*/
	fp.open(fname, ios::in | ios::out);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}

	cout << "�ļ�����" << file_length(fp) << "�ֽ�" << endl;

	// ʹ�ļ���ԭ����������10�ֽ�
	file_resize(fname, fp, file_length(fp) - 10);

	cout << "�ļ��³���" << file_length(fp) << "�ֽ�" << endl;

	cout << "������һ���ַ���(11-50�ַ�֮��)" << endl;
	gets_s(buf);

	/* �������ַ��������ݽ��ļ��ĵڶ���ǰ10�ֽ�(�������)�滻�� */
	fp.seekg(14, ios::beg);
	buf[10] = '\0'; //ֻдǰ10�ֽڣ�������벻��10�ֽڣ���������
	fp << buf;
	fp.close();
	/* ִ�е��ˣ�������� */

	cout << "�����ļ����й۲�test.txt�ĳ����Ƿ�46�ֽڣ����õ������༭(UltraEdit��)�����test.txt�鿴" << endl;
	cout << "��C����" << endl;
	while (_getch() != 'C')
		;

	/* �ٴζ�ȡ�ļ����� */
	fp.open(fname, ios::in);
	if (!fp.is_open()) {
		cout << "open failed!" << endl;
		return -1;
	}
	cout << "�رպ��ٴ���֤���ļ�����" << file_length(fp) << "�ֽ�" << endl;
	fp.close();

	return 0;
}
