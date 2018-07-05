/*
 * Copyright (c) 2013 100ask
 *              http://www.100ask.net/
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
�ù��ߵ�ʵ���÷�:
	mkbl2 u-boot.bin bl2.bin 14336
*/

int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	int		count;
	unsigned int	checksum = 0;
	int		i;

	if (argc != 4)		// �����������������3�����ӡʹ�ð�����Ϣ
	{
		printf("Usage: mkbl2 <source file> <destination file> <size> \n");
		return -1;
	}

	BufLen = atoi(argv[3]);				// ���ַ���(14336)ת����������
	Buf = (char *)malloc(BufLen);		// ����14K�Ļ���
	memset(Buf, 0x00, BufLen);			// ���û�����Ϊ0

	fp = fopen(argv[1], "rb");			// ��ֻ���ķ�ʽ��ԭʼbin�ļ�(��u-boot.bin)
	if( fp == NULL)					// ���Ϊ�գ����ʾ��ʧ��
	{
		printf("source file open error\n");
		free(Buf);					// �ͷŸոշ���Ļ���
		return -1;
	}

	fseek(fp, 0L, SEEK_END);			// ���ļ�λ��ָ��ָ���ļ�ĩβ���������е�ͳ�ƴ�С�Ĳ���
	fileLen = ftell(fp);					// ���ڵõ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ���,���ļ���С
	fseek(fp, 0L, SEEK_SET);				// ���ļ�λ��ָ��ָ���ļ���ʼ

	/* ���old.bin�ļ��Ĵ�СС�ڹ涨������С����count���ڸ��ļ��Ĵ�С�������������С */
	count = (fileLen < BufLen)? fileLen : BufLen;

	nbytes = fread(Buf, 1, count, fp);		// ��ԭʼ��bin�ļ�(��u-boot.bin)�ж�ȡcount��С�����ݵ�Buf��

	if ( nbytes != count )				// �ж��Ƿ��ȡ�ɹ�
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);							// �رոոմ򿪵�ԭʼbin�ļ�

	/* �õ�BL2 + Signature */
	for(i = 0;i < (14 * 1024) - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);
	}
	*(unsigned int*)(Buf+i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;						// ָ��Buf���׵�ַ
	nbytes	= fwrite( a, 1, BufLen, fp);	// ���õĵ�BL2 + Signatureд�뵽Ŀ���ļ���(bl2.bin)

	if ( nbytes != BufLen )				// �ж��Ƿ�д��ɹ�
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);						// ��������
	fclose(fp);

	return 0;
}
