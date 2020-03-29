#include "gtest/gtest.h"

#include "Delegate.h"

#include <iostream>

void PrintHelloWorld( ) 
{ 
	std::cout << "Hello World" << std::endl; 
}

void PrintInteger( int value )
{ 
	std::cout << value << std::endl;
}

void IncreaseOne( int& value )
{ 
	value += 1; 
}

void PrintRValueInteger( int&& value ) 
{ 
	std::cout << value << std::endl;
}

int AddInteger( int lhs, int rhs ) 
{ 
	return lhs + rhs; 
}

class Bird
{
public:
	virtual void Fly( ) const
	{
		std::cout << "Fly" << std::endl;
	}
};

class Swallow : public Bird
{
public:
	virtual void Fly( )const override
	{
		std::cout << "Swallow Flying" << std::endl;
	}
};

class Printer
{
public:
	void Print( double value )
	{
		std::cout << "Print : " << value << std::endl;
	}

	void Print( int value )
	{
		std::cout << "Print : " << value << std::endl;
	}
};

class Calculator
{
public:
	int Mul( int lhs, int rhs ) const
	{
		return lhs * rhs;
	}
};

TEST( DelegateTest, 01_Function_delegate_creation )
{
	FunctionDelegate helloWorld( &PrintHelloWorld );
	helloWorld.Execute( );
}

TEST( DelegateTest, 02_Member_function_delegate_Creation )
{
	Bird bird;

	MemberFunctionDelegate sparrow( &bird, &Bird::Fly );
	sparrow.Execute( );
}

TEST( DelegateTest, 03_Functor_delegate_creation )
{
	FunctorDelegate nonReturnValueDelegate( []( ) { std::cout << "Hello Lambda" << std::endl; } );
	nonReturnValueDelegate.Execute( );
}

TEST( DelegateTest, 04_Function_delegate_with_argument )
{
	FunctionDelegate printInt( &PrintInteger );
	printInt.Execute( 12 );

	int value = 0;

	FunctionDelegate increaseOne( &IncreaseOne );
	increaseOne.Execute( value );

	ASSERT_EQ( value, 1 );

	FunctionDelegate printRValueInt( &PrintRValueInteger );
	printRValueInt.Execute( 1 );
}

TEST( DelegateTest, 05_Member_function_delegate_with_argument )
{
	Printer printer;

	MemberFunctionDelegate<false, Printer, void, double> memberFuctionDelegate( &printer, &Printer::Print );
	memberFuctionDelegate.Execute( 123.456 );
}

TEST( DelegateTest, 06_Functor_delegate_with_argument )
{
	auto lambda = []( float value ) { std::cout << value << std::endl; };
	FunctorDelegate<decltype( lambda ), float> printFloat( lambda );
	printFloat.Execute( 12.34f );
}

TEST( DelegateTest, 07_Function_delegate_with_return_value )
{
	FunctionDelegate add( &AddInteger );
	ASSERT_EQ( add.Execute( 1, 2 ), 3 );
}

TEST( DelegateTest, 08_Member_function_delegate_with_return_value )
{
	Calculator calc;

	MemberFunctionDelegate mulDelegate( &calc, &Calculator::Mul );
	ASSERT_EQ( mulDelegate.Execute( 5, 6 ), 30 );
}

TEST( DelegateTest, 09_Functor_delegate_with_return_value )
{
	auto sub = []( int lhs, int rhs ) { return lhs - rhs; };
	FunctorDelegate<decltype( sub ), int, int> subDelegate( sub );
	ASSERT_EQ( subDelegate.Execute( 3, 4 ), -1 );
}

TEST( DelegateTest, 10_Delegate )
{
	Delegate<void> delegate;

	delegate.BindFunction( &PrintHelloWorld );
	delegate.Execute( );

	delegate.Unbind( );

	Swallow swallow;

	delegate.BindMemberFunction( &swallow, &Swallow::Fly );
	delegate.Execute( );

	delegate.BindFunctor( []( ) { std::cout << "Hello Lambda" << std::endl; } );
	delegate.Execute( );

	auto lambda = []( ) { std::cout << "Hello Lambda" << std::endl; };
	delegate.BindFunctor( lambda );
	delegate.Execute( );
}

TEST( DelegateTest, 10_Delegate_with_argument )
{
	Delegate<void, int> delegate;

	delegate.BindFunction( &PrintInteger );
	delegate( 1 );

	Printer printer;

	delegate.BindMemberFunction( &printer, &Printer::Print );
	delegate( 2 );

	delegate.BindFunctor( []( int value ) { std::cout << value << std::endl; } );
	delegate( 3 );
}

TEST( DelegateTest, 11_Delegate_with_return_value )
{
	Delegate<int, int, int> delegate;

	delegate.BindFunction( &AddInteger );
	ASSERT_EQ( delegate( 1, 2 ), 3 );

	Calculator calc;
	delegate.BindMemberFunction( &calc, &Calculator::Mul );
	ASSERT_EQ( delegate( 3, 4 ), 12 );

	delegate.BindFunctor( []( int lhs, int rhs ) { return lhs - rhs; } );
	ASSERT_EQ( delegate( 5, 6 ), -1 );
}

TEST( DelegateTest, 12_Multicast_Delegate )
{
	MulticastDelegate<int> delegate;

	DelegateHandle hPrintInteger = delegate.AddFunction( &PrintInteger );

	Printer printer;

	DelegateHandle hPrint = delegate.AddMemberFunction( &printer, &Printer::Print );

	DelegateHandle hLambda = delegate.AddFunctor( []( int value ) { std::cout << "Lambda : " << value << std::endl; } );

	delegate( 1 );

	delegate.Remove( hLambda );

	delegate( 2 );
}