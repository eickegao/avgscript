#include "CFileSystem_win.h"


int main(int argc,char* argv[])
{
	
	CFileList * dir_files = new CFileList;
	CFileSystem::GetDirFiles(".",dir_files);
	printf("1 Ŀ¼�ļ����ʲ��� ��%d��Ŀ¼���ļ�\n",dir_files->size());
	for (int i =0 ;i<dir_files->size();i++) {
		if(!(*dir_files)[i]->IsDirectory())
			printf("�ļ�: %s\n",(*dir_files)[i]->m_filename.c_str());
		else
			printf("Ŀ¼: %s\n",(*dir_files)[i]->m_filename.c_str());
	}

	//�������ԡ�
	printf("2 �ļ���������\n");
	printf("�ļ�����%s\n",CFileSystem::CopyFile("main.cpp","main.bak")==true?"�ɹ�":"ʧ��");
	printf("3 Ŀ¼��������\n");
	printf("Ŀ¼����1%s\n",CFileSystem::CopyDir( "Debug", "Debug1" )==true?"�ɹ�":"ʧ��");
	printf("Ŀ¼����2%s\n",CFileSystem::CopyDir( "Debug", "Debug2" )==true?"�ɹ�":"ʧ��");
	printf("4 Ŀ¼ɾ������,�밴�س�������....\n");
	getchar();
	printf("Ŀ¼ɾ��%s\n",CFileSystem::DeleteDir("Debug2" )==true?"�ɹ�":"ʧ��");
	printf("���Խ���\n");
	CFileSystem::Rename("main.bak","main.bak2");
	//getchar();
	return 1;
}