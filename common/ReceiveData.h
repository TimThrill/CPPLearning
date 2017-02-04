class ReceiveData
{
	public:
	ReceiveData();
	int ReadData(char* writeBuff);
	private:
	int readWindow;
	int socket;
};
