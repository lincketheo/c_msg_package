# Serialization library 
The primary serialization protocols are in c, in the c folder, however, c++ is going to be supported;

# Usage:

```
$ make
$ ./run # runs cpp/main.cpp
```

## A note on endianness
Eventually, endianness will be built in, but for now, change

./c/src/data.h

The following lines
```
// either:
#define __RMT_BYTE_ORDER__ __RMT_BIG_ENDIAN__ 

// or
#define __RMT_BYTE_ORDER__ __RMT_BIG_ENDIAN__ 
```


## Learn by Example:
Consider the example serialize sequence using the c standard serialization library

```c

// Create buffer initializes the header and internal data
data_buffer buff = create_buffer();

// Lets declare some data to serialize see type_codes.h for the appicable types you can use
int i = 3;
const char* data = "Hello World";
double j = 8.123123123;
int64_t k = 10000000000000000;
const int vals[4] = { 0, 1, 2, 3 };

// Now we can serialize data
serialize_data(&buff, &i, sizeof(int), INT);
serialize_data(&buff, data, strlen(data), STRING);
serialize_data(&buff, &j, sizeof(double), DOUBLE);
serialize_data(&buff, &k, sizeof(int64_t), INT64);
serialize_data(&buff, vals, sizeof(vals), INT | ARRAY); //TODO - need to impliment orring like this


// to wire packs header into the buffer
to_wire(&buff);

// This is the actual data we'd wend over the wire
const uint8_t* wire_data = buff.data;

uint8_t buffer[256];
element first = get_data(wire_data, buffer, 0);
element second = get_data(wire_data, buffer, 1);
element third = get_data(wire_data, buffer, 2);
...

/*
  first.data is the pointer to the data (i.e. &i or 3)
  second.data is the pointer to the second data (i.e. data = "Hello World")

  etc.

  buffer is simply a place to hold data, 
  you can have a value before hand to serialize 
  into, such as an int or string, but get_data 
  has a ton of checks
*/

```




## Application
Of course, a message is passed over the wire, so there is no meta information, meaning message class need to be robust in reading from an incomming char array.

A message is built as follows:

### Header
byte1 [enianness    ] // Endianness is not implimented in base c library, implimentation specific code needs to account for this

byte2 [message type ] // Right now, I have ping messages (empty data) and data message (with data) but I might add more

byte3 [flags        ] // Simple communication, useful for ping messages

byte4 [protocol     ] // Right now, msg package is protocol version 1, but in the future it might change

byte5 [byte size    ] // uint32_t Size of message in bytes (max 4096)

byte6 ...

byte7 ... 

byte8 ...

byte9 [fields       ] // uint16_t number of fields (max 1^7)

byte10 ...

byte11 [0x00        ] // Two nullterminators

byte12 [0x00        ]

[DATA]




### Data
byte1 [byte size    ] // Size of data

byte2 [type code    ] // Type codes are defined in type_codes.h

byte3 [DATA         ]

....

byten [0x00         ] // Null terminator

## Methods for traversing messages
Messages are not two way or O(1) searchable. At the most complex, it is O(n), which could be fixed using some larger message structures, but our priority is not latency, it is data transmission. That's why our data is in as small packets as possible

#### Algorithm for traversing messages
1. Start at the data head (data[12])
2. Count size for each data header and incriment byte
3. If not the right index, move on size + 3 (null, size and type code offer 3 bytes of padding)
4. If the correct index, return type code and copy memory at index + 2
