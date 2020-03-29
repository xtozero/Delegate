# Delegate
[![Build Status](https://travis-ci.com/xtozero/Delegate.svg?token=XYF23kpdHvwmmWT7kJzc&branch=master)](https://travis-ci.com/xtozero/Delegate)[![Build status](https://ci.appveyor.com/api/projects/status/34liphxupa2civv6?svg=true)](https://ci.appveyor.com/project/xtozero/delegate)[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/xtozero/Delegate.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/xtozero/Delegate/context:cpp)

Simple delegate, written in c++ 17

## How to build

### in Visual Studio 2017

1. Clone repository.

2. Create 'Build' Folder in repository folder.

3. Open command line.

4. Move directory to 'Build' Folder.

5. Type in command line.

   ```bash
   cmake .. -G "Visual Studio 15 Win64"
   ```

6. Open solution file and Build.

## Usage

### Unicast Delegate

```C++
// for 'void(void)'' function
Delegate<void> delegate;

// function
delegate.BindFunction( &PrintHelloWorld );
delegate.Execute( );

// unbind
delegate.Unbind( );

Swallow swallow;

// member function
delegate.BindMemberFunction( &swallow, &Swallow::Fly );
delegate.Execute( );

// lambda or functor
delegate.BindFunctor( []( ) { std::cout << "Hello Lambda" << std::endl; } );
delegate.Execute( );

auto lambda = []( ) { std::cout << "Hello Lambda" << std::endl; };
delegate.BindFunctor( lambda );
delegate.Execute( );
```

### Multicast Delegate

```C++
MulticastDelegate<int> delegate;

// Add function
DelegateHandle hPrintInteger = delegate.AddFunction( &PrintInteger );

Printer printer;

// Add member function
DelegateHandle hPrint = delegate.AddMemberFunction( &printer, &Printer::Print );

// Add lambda or functor
DelegateHandle hLambda = delegate.AddFunctor( []( int value ) { std::cout << "Lambda : " << value << std::endl; } );

// Call delegate
delegate( 1 );

// Remove by handle
delegate.Remove( hLambda );

delegate( 2 );
```

