I think there are a few mistakes in the code that the book gives us.
There is one in particular that may cause a buffer overflow.

The following code snippet is from function `Personal::writeToFile()`. These
two functions can be found in the `student.cpp` file.

```c++
  out.write(reinterpret_cast<const char*>(&year), sizeof(int));
  out.write(reinterpret_cast<const char*>(&salary), sizeof(int));
```

and the following is from the function `Personal::readFromFile()`

```c++
  in.read(reinterpret_cast<char*>(&year), sizeof(int));
  in.read(reinterpret_cast<char*>(&salary), sizeof(int));
```

Now, when students enter in information for salary, they may get a
very big number. I think this is because a buffer overflow is
occuring. The class defines the variable salary to be of data type
long, which is 8-bytes but the stream writes and records a buffer size
of 4-bytes for data type int. I think it should be changed to this
instead:

```c++
  out.write(reinterpret_cast<const char*>(&year), sizeof(int));
  out.write(reinterpret_cast<const char*>(&salary), sizeof(long));
```

  and

```c++
  in.read(reinterpret_cast<char*>(&year), sizeof(int));
  in.read(reinterpret_cast<char*>(&salary), sizeof(long));
```

There is another buffer overflow bug in `Student::readFromConsole` from
the `student.cpp` file.

```c++
  istream& Student::readFromConsole(istream& in) {
    char s[80];
    cout << "Major: ";
    in.getline(s,80);
    strncpy(major,s,9);        // This line is what the book has
    strncpy(major,s,majorLen); // <- But it should be this instead
  }
```

I haven't received any weird values for this one yet, but my debugger
stopped complaining once I adjusted the buffer size from 9 to `majorLen`.
