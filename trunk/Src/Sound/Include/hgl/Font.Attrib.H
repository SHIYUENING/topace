	static Font *DefaultFont;

private:

	String name;

	int width,height;
	bool bold,italic;

protected:
		
	void GetName();
	void SetName();

	int GetWidth(){return width;}
	int GetHeight(){return height;}
	bool GetBold(){return bold;}
	bool GetItalic(){return italic;}

	void SetWidth(int);
	void SetHeight(int);
	void SetBold(bool);
	void SetItalic(bool);
		
	void InitPrivate();
