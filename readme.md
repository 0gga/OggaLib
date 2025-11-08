# **OggaLib**<br>

> ## **How To Use**<br>
> In .gitmodule append:
>```.ini
>[submodule "extern/ogga"]  
>    path = extern/ogga  
>    url = https://github.com/0gga/oggaLib.git
>```
> Run `git submodule add https://github.com/0gga/oggaLib.git extern/ogga` in root to add to .git/config  
> Then run `git submodule update --init --recursive`