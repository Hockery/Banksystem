#include "lead.h"

void openAccount()//�������ڽṹ������������һ�������Ա����һ����������Ϣ��
{
	int accNumber;//�˺�
	char accName[9];//�˻���
	char accPWD[7];//�˻�����
	double cash;//�ֽ����
	//��ʼ��
	accNumber = 0;
	memset(accName, 0, sizeof(accName));
	memset(accPWD, 0, sizeof(accPWD));
	cash = 0;
	accNumber = creatAccNumber();
	getaccName(accName);
	getaccPWD(accPWD);
	cash = getcash(0);

	maxAccount++;

	//����ֵ��ֵ���ṹ��������
	rs[maxAccount].accNumber = accNumber;
	strcpy(rs[maxAccount].accName, accName);
	strcpy(rs[maxAccount].accPWD, accPWD);
	rs[maxAccount].balance = cash;
	strcpy(rs[maxAccount].flag, "0");
	//ÿ��һ��������ʱ��������
	if (writeData())
	{
		printf("д�ļ�����");
		return;
	}
	dispAnAccount(maxAccount);
	printf("�����ɹ����󼪴������ϳԼ���\n");
	getchar();
}

void deposit()//���������ӵ����˻�������ϣ�
{
	int	accNumber = 0;
	int weizhi = -1;
	double cash = 0;
	accNumber = getaccNumber(0);
	weizhi = findAnAccount(accNumber);
	if (weizhi == -1)
	{
		printf("���޴��˻��������������...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("���˻��Ѿ����������ܴ������������...\n");
		getchar();
		return;
	}
	cash = getcash(0);
	rs[weizhi].balance += cash;

	if (writeData())
	{
		printf("д�ļ�����");
		return;
	}

	dispAnAccount(weizhi);
	printf("���ɹ�����������������˵�...\n");
	getchar();
}
void withdraw()//ȡ��Ӹ��˻�������Ͽ۳�ȡ���
{
	int accNumber, i,j,choice;
	char accPWD[7];
	char accName[9];
	int weizhi;
	double cash;
	
	accNumber = 0;
	weizhi = -1;
	cash = 0;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    ���ʺŲ�ѯ  �밴1     |\n");
	printf("|    ��������ѯ  �밴2     |\n");
	printf("+--------------------------+\n");
	printf("����������ѡ��");
	scanf("%d", &choice);
	if (choice==1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice==2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi==-1)
	{
		printf("���޴��˻��������������...\n");
		getchar();
		getchar();
		return;
	}

	for ( i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD,accPWD)==0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("�������벻��ȷ�����������룡\n");
			}
			else
			{
				printf("���벻��ȷ�������������...\n");
				getchar();
				return;
			}
		}
	}

	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("���˻��Ѿ�����������ȡ������������...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);

	cash = getcash(1);
	if (cash>rs[weizhi].balance)
	{
		printf("ȡ������˻�������͸֧�������������...\n");
	}
	else
	{
		rs[weizhi].balance -= cash;
	}
	if (writeData())
	{
		printf("д�ļ�����\n");
		return;
	}
	dispAnAccount(weizhi);
	printf("ȡ��ɹ�����������������˵�...\n");
	getchar();
	getchar();
}
void query()//��ѯ����ѯĳ�˻���Ϣ��
{
	int accNumber, i, j, choice;
	char accPWD[7];
	char accName[9];
	int weizhi;

	accNumber = 0;
	weizhi = -1;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    ���ʺŲ�ѯ  �밴1     |\n");
	printf("|    ��������ѯ  �밴2     |\n");
	printf("+--------------------------+\n");
	printf("����������ѡ��");
	scanf("%d", &choice);
	if (choice == 1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice == 2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi == -1)
	{
		printf("���޴��˻��������������...\n");
		getchar();
		getchar();
		return;
	}

	for (i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD, accPWD) == 0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("�������벻��ȷ�����������룡\n");
			}
			else
			{
				printf("���벻��ȷ�������������...\n");
				getchar();
				return;
			}
		}
	}

	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("��ѯ�����˻��Ѿ������������������...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	getchar();
	getchar();
}

void closeAccount()//�����������˻����˻�״̬��Ϊ1���˻������Ϊ0��
{
	int accNumber, i, j, choice;
	char accPWD[7];
	char accName[9];
	char count[2];
	int weizhi;

	accNumber = 0;
	weizhi = -1;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    ���ʺŲ�ѯ  �밴1     |\n");
	printf("|    ��������ѯ  �밴2     |\n");
	printf("+--------------------------+\n");
	printf("����������ѡ��");
	scanf("%d", &choice);
	if (choice == 1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice == 2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi == -1)
	{
		printf("���޴��˻��������������...\n");
		getchar();
		getchar();
		return;
	}

	for (i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD, accPWD) == 0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("�������벻��ȷ�����������룡\n");
			}
			else
			{
				printf("���벻��ȷ�������������...\n");
				getchar();
				return;
			}
		}
	}
	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("��ѯ�����˻��Ѿ������������������...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    ����   �밴�ǡ�Y��    |\n");
	printf("|    ����   �밴��N��    |\n");
	printf("+--------------------------+\n");
	printf("����������ѡ��");
	scanf("%s",count);
	if (strcmp(count,"Y")==0)
	{
		if (rs[weizhi].balance!=0)
		{
			printf("�˻���%12.2f", rs[weizhi].balance);
			printf("�뵽���а���ȡ������������\n");
			strcpy(rs[weizhi].flag, "1");
			dispAnAccount(weizhi);
		}
		else if (rs[weizhi].balance==0)
		{
			printf("�˻���%12.2f", rs[weizhi].balance);
			strcpy(rs[weizhi].flag, "1");
			rs[weizhi].balance = 0;
			dispAnAccount(weizhi);
		}
	}
	else if (strcmp(count, "N") == 0)
	{
		mypause();
		return;
	}
	else
	{
		printf("ѡ����Ч��");
		mypause();
		return;
	}
	getchar();
	getchar();
}