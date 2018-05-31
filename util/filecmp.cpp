#include <cstdio>
#include <memory>
#include <cstring>

using namespace std;
int main(int argc, char *argv[])
{
	if (!strcmp(argv[1], argv[2]))
	{
		printf("�ļ���һ��\n");
	}
	FILE *fp1 = fopen(argv[1], "rb");
	FILE *fp2 = fopen(argv[2], "rb");
	shared_ptr<FILE> raii1(fp1, fclose);
	shared_ptr<FILE> raii2(fp2, fclose);
	if (!fp1)
	{
		raii1.reset();
	}
	if (!fp2)
	{
		raii2.reset();
	}
	if (!fp1 || !fp2)
	{
		printf("�޷����ļ�\n");
	}
	fseek(fp1, 0, SEEK_END);
	int len1 = ftell(fp1);

	fseek(fp2, 0, SEEK_END);
	int len2 = ftell(fp2);

	if (len1 != len2)
	{
		printf("���Ȳ�һ��:%d %d\n", len1, len2);
		return 0;
	}
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);
	char ch1, ch2;
	ch1 = std::fgetc(fp1);
	ch2 = std::fgetc(fp2);
	long long diff_point = 0;
	while (ch1 != EOF)
	{
		if (ch1 != ch2)
		{
			printf("�ļ���һ��:%lld\n", diff_point);
			return 0;
		}
		ch1 = std::fgetc(fp1);
		ch2 = std::fgetc(fp2);
		diff_point++;
	}
	printf("�ļ�һ��");
	return 0;
}