#ifndef Special_H
#define Special_H

class Special
{
	//	--	Class Variables	--

protected:
	int strMod;			// 0
	int agiMod;			// 1
	int sklMod;			// 2
	int wlpMod;			// 3

	int movMod;			// 4
	int physResMod;		// 5
	int mntlResMod;		// 6
	float accMod;		// 7
	float crtMod;		// 8

	// Should make a noCrit bool

	float dgdMod;		// 9
	int thrtMod;		// 10

	int dmgMod;			// 11

	int strReq;			// 12
	int agiReq;			// 13
	int sklReq;			// 14
	int wlpReq;			// 15

	//	--	End Class Variables	--


	//	--	Constructors/Destructors	--

public:
	Special(void);
	~Special(void);

	//	--	End Constructors/Destructors	--


	//	--	Methods	--
	
	///	Note that implementation for template functions/classes cannot be separated.
	///	It must go in the header to be used in other classes.
	///	That being the case. . .I should really find another way to do this.
	///
	template <typename T>
	void SetMod(int index, T val)
	{
		switch (index)
		{
			case 0:		// strMod
			{
				strMod = val;
				break;
			}
			case 1:		// agiMod
			{
				agiMod = val;
				break;
			}
			case 2:		// sklMod
			{
				sklMod = val;
				break;
			}
			case 3:		// wlpMod
			{
				wlpMod = val;
				break;
			}
			case 4:		// movMod
			{
				movMod = val;
				break;
			}
			case 5:		// physResMod
			{
				physResMod = val;
				break;
			}
			case 6:		// mntlResMod
			{
				mntlResMod = val;
				break;
			}
			case 7:		// accMod
			{
				accMod = val;
				break;
			}
			case 8:		// crtMod
			{
				crtMod = val;
				break;
			}
			case 9:		// dgdMod
			{
				dgdMod = val;
				break;
			}
			case 10:	// thrtMod
			{
				thrtMod = val;
				break;
			}
			case 11:	// dmgMod
			{
				dmgMod = val;
				break;
			}
			case 12:	// strReq
			{
				strReq = val;
				break;
			}
			case 13:	// agiReq
			{
				agiReq = val;
				break;
			}
			case 14:	// sklReq
			{
				sklReq = val;
				break;
			}
			case 15:	// wlpReq
			{
				wlpReq = val;
				break;
			}
		}
	}

	//	--	End Methods	--

};

#endif