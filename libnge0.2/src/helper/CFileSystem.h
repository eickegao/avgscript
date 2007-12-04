#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#ifdef WIN32
#else
#endif



/**
 * �ļ����Զ��壬��sony�Ķ�����ͬ��
 */
enum eAttributeFlags
{
	AF_READ_ONLY	= ( 1 << 0 ),
	AF_HIDDEN	= ( 1 << 1 ),
	AF_UNKNOWN1	= ( 1 << 2 ),
	AF_UNKNOWN2	= ( 1 << 3 ),
	AF_DIRECTORY	= ( 1 << 4 ),
	AF_ARCHIVE	= ( 1 << 5 ),
	AF_DOT_DOT	= ( 1 << 30 ),
	AF_DRIVE	= ( 1 << 31 ),
};

#ifdef WIN32

struct SceIoStat
{
	int st_mode;
};
#define SceUID int
#endif


struct sDirEntry
{
	string		m_filename;
	SceIoStat	m_stats;
	/**
	 * ��ǰ�����Ƿ���һ���ļ���
	 * @param ��
	 * @return bool,�纯������ʾ��
	 */
	bool		IsFile() const			{ return ( IsDrive() == false && IsDotDot() == false && IsDirectory() == false ); }
	/**
	 * ��ǰ�����Ƿ���һ���̷���
	 * @param ��
	 * @return bool,�纯������ʾ��
	 */
	bool		IsDrive() const			{ return ( m_stats.st_mode & AF_DRIVE ); }
	/**
	 * ��ǰ�����Ƿ���һ����Ŀ¼��[..]��
	 * @param ��
	 * @return bool,�纯������ʾ��
	 */
	bool		IsDotDot() const		{ return ( m_stats.st_mode & AF_DOT_DOT ); }
	/**
	 * ��ǰ�����Ƿ���һ��Ŀ¼��
	 * @param ��
	 * @return bool,�纯������ʾ��
	 */
	bool		IsDirectory() const		{ return ( ( m_stats.st_mode & FIO_S_IFDIR ) & FIO_S_IFMT ); }
};

typedef list< sDirEntry > CFileList;

typedef SceUID	FIND_FILE_HANDLE;

/**
 * �ļ���д�ࡣ
 */
class CFile
{
	public:
		/**
		 * ���ļ�������
		 * @param void*,��ȡ�ļ���λ�á�
		 * @param int32,��ȡ�ļ��ĳ��ȡ�
		 * @param int*, ʵ�ʶ�ȡ�ļ��ĳ��ȡ�
		 * @return bool,�ɹ�Ϊtrue��ʧ��Ϊfalse��
		 */
		bool			Read( void * p_address, u32 length, u32 * p_nbytes_read = NULL ) const;
		/**
		 * д�ļ�������
		 * @param void*,д���ļ���λ�á�
		 * @param int32,д���ļ��ĳ��ȡ�
		 * @param int*, ʵ��д���ļ��ĳ��ȡ�
		 * @return bool,�ɹ�Ϊtrue��ʧ��Ϊfalse��
		 */
		bool			Write( const void * p_address, u32 length, u32 * p_nbytes_written = NULL ) const;
		/**
		 * �Ƿ񵽴��ļ�β��
		 * @param �޲�����
		 * @return bool,����true����false��
		 */
		bool			IsEOF() const;
		/**
		 * ����ļ����ȡ�
		 * @param �޲�����
		 * @return int,�����ļ��ĳ��ȡ�
		 */
		u32			GetLength() const;
		/**
		 * ����ļ����ȡ�
		 * @param �޲�����
		 * @return int,�����ļ��ĳ��ȡ�
		 */
		u32			Tell() const;
		/**
		 * �ƶ��ļ�ָ��λ�á�
		 * @param int,����ڳ�ʼλ�õ�ƫ�ơ�
		 * @param int,ͬSEEK_END,SEEK_SET,SEEK_CUR.
		 * @return int,���سɹ�ʧ�ܱ�־��
		 */
		bool			Seek( const u32 offset, const u32 origin ) const;
		/**
		 * ��һ���ַ���ͬfgetchar��
		 * @param ,�ޡ�
		 * @return char,�����ַ����ļ�ָ��+1��ͬfgetchar����
		 */
		char			GetChar() const;
	protected:
		CFile( const char* filename, FILE * const handle );
		~CFile();
	private:
		string			m_filename;
		FILE *			m_phandle;
		u32			m_length;
};

/**
 * �ļ������ࡣ
 */
class CFileSystem
{
	public:
		/**
		 * ���ù���·����ͬchdir��
		 * @param const char*,����Ŀ¼����
		 * @return bool,true/false��
		 */
		static bool		SetWorkDir( const char * dir );
		/**
		 * ��һ���ļ��������ļ���д�ࡣ
		 * @param const char*,�򿪵��ļ�����
		 * @param const char*,�򿪵ı�־��ͬfopen��
		 * @return CFile*,�ļ���д���ָ�롣
		 */
		static CFile *		Open( const char * filename, const char * const open_flags );
		/**
		 * �ر�һ���ļ���
		 * @param CFile * const,�ļ���д���ָ�롣
		 * @return bool,true/false��
		 */
		static void		Close( CFile * const pfile );
		/**
		 * �Ƿ��ļ����ڡ�
		 * @param const char*,�ļ�����
		 * @return bool,true/false��
		 */
		static bool		IsFileExists( const char * filename );
		/**
		 * �Ƿ�Ŀ¼���ڡ�
		 * @param const char*,Ŀ¼����
		 * @return bool,true/false��
		 */
		static bool		IsDirExists( const char * dir );
		/**
		 * �õ�dir�������ļ����б������ڵڶ�������CFileListָ���С�
		 * @param const char*,Ŀ¼����
		 * @param const CFlieList*,��ȡ���ļ��б�
		 * @return bool,true/false��
		 */
		static bool		GetDirFiles( const char * dir,const CFileList * dir_files );
		
		static bool		FindFirstFile( const char * path, const FIND_FILE_HANDLE * handle );
		static bool		FindNextFile( const sDirEntry * dir_entry, FIND_FILE_HANDLE handle );
		static bool		FindCloseFile( FIND_FILE_HANDLE handle );
		/**
		 * ����һ���ļ���
		 * @param const char*,Ҫ����Դ�ļ�����
		 * @param const char*,Ҫ��������Ŀ���ļ�����
		 * @return bool,true/false��
		 */
		static bool		CopyFile( const char * src_file, const char * dst_file );
		/**
		 * ����һ��Ŀ¼��
		 * @param const char*,Ҫ����ԴĿ¼����
		 * @param const char*,Ҫ��������Ŀ��Ŀ¼����
		 * @return bool,true/false��
		 */
		static bool		CopyDir( const char * src_dir, const char * dst_dir );
		/**
		 * ɾ��һ���ļ�
		 * @param const char*,Ҫɾ�����ļ�����
		 * @return bool,true/false��
		 */
		static bool		DeleteFile( const char * filename );
		/**
		 * ɾ��һ��Ŀ¼
		 * @param const char*,Ҫɾ����Ŀ¼����
		 * @return bool,true/false��
		 */
		static bool		DeleteDir( const char * dir );
		/**
		 * ����һ��Ŀ¼
		 * @param const char*,Ҫ������Ŀ¼����
		 * @return bool,true/false��
		 */
		static bool		MakeDir( const char * dir );
		/**
		 * ���ϵ��ļ�������Ϊ�µ��ļ�����
		 * @param const char*,Ҫ�޸ĵľɵ��ļ�����
		 * @param const char*,�ı�ɵ��µ��ļ�����
		 * @return bool,true/false��
		 */
		static bool		Rename( const char * old_name, const char * new_name );
		/**
		 * ���ļ���������Ϊֻ����
		 * @param const char*,Ҫ����ֻ�����ļ�����
		 * @return bool,true/false��
		 */
		static bool		MakeReadOnly( const char * filename );
		/**
		 * ���ļ���������Ϊ��д��
		 * @param const char*,Ҫ���ÿ�д���ļ�����
		 * @return bool,true/false��
		 */
		static bool		MakeWritable( const char * filename );
		/**
		 * ����һ���ļ���ȫ·��������·������
		 * @param const char*,Ҫ����ȫ·�����ļ�����
		 * @return string,�ļ���ȫ·��������·������
		 */
		static string		MakeFullPath( const char * filename );
		/**
		 * ���һ���ļ�����չ��������c://dev/test.mp3�ͻ���ַ���mp3��
		 * @param const char*,�ļ�����
		 * @return string,�ļ�����չ����
		 */
		static string		GetFileExtension( const char * filename );
		/**
		 * ����һ��·�����ֱ�������Ӧ���С�
		 * @param const char*,��������·����
		 * @param const char*,�̷���
		 * @param const char*,Ŀ¼����
		 * @param const char*,�ļ�����
		 * @param const char*,��չ����
		 * @return �޷���ֵ��
		 */
		static void		SplitPath( const char * path, const char * drive, const char * dir, const char * fname, const char * ext );
	private:
		#ifdef WIN32
		CFileFind       m_filefind;
		#else
		static SceIoDirent	m_direntry;
		#endif
		static string		m_workdir;
};



#endif
