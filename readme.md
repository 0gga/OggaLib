# **NFC Reader System**<br>

> ## **Dependencies**<br>
>
>> Run `git submodule update --init --recursive` in root to clone external dependencies:
>
>
>> ### **Current dependencies:**
>>
>>- **boost.asio**  
>>  Read documentation for info on sub-dependencies  
>>- **nlohmann/json**

> ## **CLI Syntax & Cmdlets**<br>
>
>> ### **Syntax**<br>
>>
>>_**To make the CLI commands parseable, they must be syntactically correct:**_  
>> CLI command arguments must always be separated by a single space,  
>> and must never have any trailing spaces:  
>> `newUser john 3`
>>
>>User or door names must be either snake_case or camelCase:  
>> `rmUser johnDoe`  
>> `rmUser john_doe`  
>> The CLI parser will look for both and ensure all entries are removed.
>>
>>If exceptions are made such as PascalCase or PascalSnake_Case,  
>> it will still work as long as the preceding letter to a surname is lower case:  
>> `rmDoor JohnDoe`  
>> `rmDoor John_Doe`  
>> `rmDoor JOHN_Doe`
>>
>>The following combinations will not work:  
>> `newUser JOHNDOE`  
>> `newUser johNdoe`
>
>> ### **Cmdlets**<br>
>>
>>- Add a new door by name: `newDoor <string>door1 <int>accesslevel`
>>- Create a new user: `newUser <string>0gga <int>accesslevel`
>>- Remove an existing user: `rmDoor <string>door1`
>>- Remove an existing user: `rmUser <string>0gga`
>>- Shutdown the CLI connection: `shutdown`
>>- Get client logs: `getLog`
>>
>>
>>#### **Possible additions:**
>>
>>- Get user specific logs: `getULog 0gga`

> ## **Compilation**<br>
>> ### **Cross Compilation**<br>
>>CMake is used for compilation and works well with any toolchain.  
> > Use CLion WSL toolchain for easy cross compilation.

> ## **Features**<br>
>> ### **Implemented**<br>
>>- Easy Admin configuration through CLI connection on a separate port.
>>- Constantly accepts clients and stores information independently.
>>- Systemwide unified users.json - read onto hashmaps at startup for efficient runtime.
>>- String parser for standardized name format - snake_case.  
>> <br>
>>- ASIO - Asynchronous client handling.
>>- Asynchronous client handling runs on hardcoded amount of dedicated threads{4}.
>>- Callback to avoid blocking IO.
>>- Utilizes shared_lock & unique_lock for read/write respectively.
>> <br>
>>- OOP implementation for simple high-level usage.
>
>> ### **To be implemented**<br>
>>- The system currently doesn't write systemwide logs nor user logs,<br>
    albeit this could easily be implemented since clients are already assigned names.