// Made on Dev-C++

#include <iostream>
using namespace std;
int main ()
{
	int a,b,c,i,o,sBBQizza,mBBQpizza,lBBQpizza,sFpizza,mFpizza,lFpizza,sSpizza,mSpizza,lSpizza,sshaurma,mshaurma,lshaurma,szinger,mzinger,lzinger,dew,pepsi,coke,pizza,shaurma,zinger,CD,gtotal;
	sBBQizza=mBBQpizza=lBBQpizza=sFpizza=mFpizza=lFpizza=sSpizza=mSpizza=lSpizza=sshaurma=mshaurma=lshaurma=szinger=mzinger=lzinger=dew=pepsi=coke=pizza=shaurma=zinger=CD=gtotal=0;
	i=1;
	o=1;
	float price,total,titems;
	price=total=titems=0;
	cout << ":):):):):):):):):):) WELCOME (:(:(:(:(:(:(:(:(:(:" << endl << endl;
	cout << "Press 1 for Pizza" << endl;
	cout << "Press 2 for Shaurma" << endl;
	cout << "Press 3 for Zinger" << endl;
	cout << "Press 4 for Cold Drink" << endl;
	cout << "Press 0 to Exit without Buying anything!" << endl;
	while (o<=5)
	{
	o++;
	cin >> a;
	if(a==0)
	{
		break;
	}
	
	switch(a)
	{
		case 1 : //for pizza
		{
			cout << "Specify Flavour!" << endl;
			cout << "Press 1 for BBQ" << endl;
			cout << "Press 2 for Fajita" << endl;
			cout << "Press 3 for Supreme" << endl;
			cin >> b;
			switch(b)
			{
				case 1 : //for BBQ pizza
				{
					cout << "Size?" << endl;
					cout << "Press 1 for small" << endl;
					cout << "Press 2 for medium" << endl;
					cout << "Press 3 for larger" << endl;
					cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
					cout << "Press 0 to Exit" << endl;
					while (i<=5)
					{
					i++;
					cin >> c;
					if(c==0)
					{
						total-=price;
						break;	
					}
					switch(c)
					{
						case 1: //for small BBQ	
						{
							price = 200 + ((200*5)/100);
							cout << "Total Price = " << price;
							sBBQizza +=1;
							break;
						}
						case 2: //for medium BBQ	
						{
							price = 300 + ((300*5)/100);
							cout << "Total Price = " << price;
							mBBQpizza +=1;
							break;
						}
						case 3: //for large BBQ	
						{
							price = 400 + ((400*5)/100);
							cout << "Total Price = " << price;
							lBBQpizza +=1;
							break;
						}
						default:
						{
							cout << "Invalid Number!" << endl;
							total-=price;
							i--;
						}
					}
					total+=price;
					cout << endl;
					
					}
					cout << "Sum = " << total;		 
				break;
				}
				case 2 : //for Fajita pizza
				{
					cout << "Size?" << endl;
					cout << "Press 1 for small" << endl;
					cout << "Press 2 for medium" << endl;
					cout << "Press 3 for larger" << endl;
					cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
					cout << "Press 0 to Exit" << endl;
					while(i<=5)
					{
					cin >> c;
					i++;
					if(c==0)
					{
						break;
					}
					switch(c)
					{
						case 1: //for small fajita
						{
							price = 250 + ((250*5)/100);
							cout << "Total Price = " << price;
							sFpizza += 1;
							break;
						}
						case 2: //for medium fajita	
						{
							price = 350 + ((350*5)/100);
							cout << "Total Price = " << price;
							mFpizza += 1;
							break;
						}
						case 3: //for large fajita
						{
							price = 450 + ((450*5)/100);
							cout << "Total Price = " << price;
							lFpizza += 1;
							break;
						}
						default:
						{
							cout << "Invalid Number!" << endl;
							total-=price;
							i--;
						}
					}
					total+=price;
					cout << endl;
					}
					cout << "Sum = " << total;		 
				break;
				}
				case 3 : //for Supreme pizza
				{
					cout << "Size?" << endl;
					cout << "Press 1 for small" << endl;
					cout << "Press 2 for medium" << endl;
					cout << "Press 3 for larger" << endl;
					cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
					cout << "Press 0 to Exit" << endl;
					while(i<=5)
					{
					cin >> c;
					i++;
					if(c==0)
					{
						break;
					}
					switch(c)
					{
						case 1: //for small Supreme
						{
							price = 300 + ((300*5)/100);
							cout << "Total Price = " << price;
							sSpizza +=1;
							break;
						}
						case 2: //for medium Supreme
						{
							price = 400 + ((400*5)/100);
							cout << "Total Price = " << price;
							mSpizza +=1;
							break;
						}
						case 3: //for large Supreme
						{
							price = 500 + ((500*5)/100);
							cout << "Total Price = " << price;
							lSpizza +=1;
							break;
						}
						default:
						{
							cout << "Invalid Number!" << endl;
							total-=price;
							i--;
						}
					}
					total=total+price;
					cout << endl;
					}
					cout << "Sum = " << total;
				break;
				}
				default:
				{
					cout << "Invalid Number";
				}
			}	
		break;
		} 
		case 2 : // for Shaurma
		{
			cout << "Size?" << endl;
			cout << "Press 1 for small" << endl;
			cout << "Press 2 for medium" << endl;
			cout << "Press 3 for larger" << endl;
			cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
			cout << "Press 0 to Exit" << endl;
			while (i<=5)
			{
			i++;
			cin >> c;
			if(c==0)
			{
				break;	
			}
		    switch(c)
			{
				case 1: //for small Shuarma
				{
					price = 100 + ((100*5)/100);
					cout << "Total Price = " << price;
					sshaurma +=1;
					break;
				}
				case 2: //for medium Shuarma
				{
					price = 125 + ((125*5)/100);
					cout << "Total Price = " << price;
					mshaurma +=1;
					break;
	 			}
				case 3: //for large Shuarma
				{
					price = 150 + ((150*5)/100);
					cout << "Total Price = " << price;
					lshaurma +=1;
					break;
				}
				default:
				{
					cout << "Invalid Number!" << endl;
					i--;
					total-=price;
				}
			}
			total+=price;
			cout << endl;
	    	}
	    	cout << "Sum = " << total;
		break;	
		}
		case 3 : // for Zinger
		{
			cout << "Size?" << endl;
			cout << "Press 1 for small" << endl;
			cout << "Press 2 for medium" << endl;
			cout << "Press 3 for larger" << endl;
			cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
			cout << "Press 0 to Exit" << endl;
			while (i<=5)
			{
			i++;
			cin >> c;
			if(c==0)
			{
				break;	
			}
			switch(c)
			{
				case 1: //for small Zinger
				{
					price = 110 + ((110*5)/100);
					cout << "Total Price= " << price;
					szinger +=1;
					break;
				}
				case 2: //for medium Zinger
				{
					price = 130 + ((130*5)/100);
					cout << "Total Price = " << price;
					mzinger +=1;
					break;
	 			}
				case 3: //for large Zinger
				{
					price = 150 + ((150*5)/100);
					cout << "Total Price = " << price;
					lzinger +=1;
					break;
				}
				default:
				{
					cout << "Invalid Number!" << endl;
					i--;
					total-=price;
				}	
			}
			total+=price;
			cout << endl;
			}
			cout << "Sum = " << total;
		break;	
		}
		case 4 : // for Cold Drink
		{
			cout << "Type?" << endl;
			cout << "Press 1 for Dew" << endl;
			cout << "Press 2 for Pepsi" << endl;
			cout << "Press 3 for Coke" << endl;
			cout << "Press these digits again when prompted to add more items (MAX '5')" << endl;
			cout << "Press 0 to Exit" << endl;
			while (i<=5)
			{
			i++;
			cin >> c;
			if(c==0)
			{
				break;	
			}
			switch(c)
			{
				case 1: //for Dew
				{
					price = 50 + ((50*5)/100);
					cout << "Total Price = " << price;
					dew +=1;
					break;
				}
				case 2: //for Pepsi
				{
					price = 50 + ((50*5)/100);
					cout << "Total Price = " << price;
					pepsi +=1;
					break;
	 			}
				case 3: //for Coke
				{
					price = 50 + ((50*5)/100);
					cout << "Total Price = " << price;
					coke +=1;
					break;
				}
				default:
				{
					cout << "Invalid Number!" << endl;
					i--;
					total-=price;
				}
			}
			total+=price;
			cout << endl;
			}
			cout << "Sum = " << total;
		break;
		}
		default :
		{
			cout << "Invalid Number!" << endl;
			o--;
			gtotal-=total;
		}
	}
	cout << endl;
	cout << "\nWant More?" << endl;
	cout << "Press 1 for Pizza" << endl;
	cout << "Press 2 for Shaurma" << endl;
	cout << "Press 3 for Zinger" << endl;
	cout << "Press 4 for Cold Drink" << endl;
	cout << "Press 0 to Exit" << endl;
	gtotal+=total;
	cout << endl;
	i=1;
	total=0;
	}
	pizza = sBBQizza+mBBQpizza+lBBQpizza+sFpizza+mFpizza+lFpizza+sSpizza+mSpizza+lSpizza;	
	shaurma = sshaurma+mshaurma+lshaurma;
	zinger = szinger+mzinger+lzinger;
	CD = dew+pepsi+coke;
	cout << "Pizzas : " << pizza << endl;
	cout << "Shaurmas : " << shaurma << endl;
	cout << "Zingers : " << zinger << endl;
	cout << "Cold Drinks : " << CD << endl;
	titems =  pizza+shaurma+zinger+CD;
	cout << "Total Items : " << titems << endl;
	if( titems>=5)
	{
		cout << "You have gotten 5% Discount for Buying more than 4 items" << endl;
		gtotal = gtotal-((gtotal*5)/100);
	}
	cout << "Grand Total = Rs " << gtotal;
	cout << endl << endl;
    cout << ":):):):):):):):):):):) THANK YOU (:(:(:(:(:(:(:(:(:(:";
	return 0;

}

