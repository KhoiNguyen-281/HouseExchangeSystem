# SED_GROUP
# House Exchange System

This project provide the system that support renting house between member within the system.

## Authors

- [@KhoiNguyen-281](https://github.com/KhoiNguyen-281)

## Architecture
The system is designed with Singleton patern
## Tech Stack
Project is create with:

**CLION:**
- IDE to support coding and run the system.
**C++20:** 
- Main programming language in this project;
**Github:**
- A cloud platform used to store versions of code, managing the process of the project
## Features

- CRUD basic features, supporting Create, Read, Update and Delete objects (Member, House, Request, Rating).
**Advance features:**
- Member can assign their house for rent, as well as request to occupy a house 
- Member can give feedback about the rented house, as well as the occupier after the house is checked out.
- Request will be automatically cancelled if the date is dued.


## Deployment

To deploy this project,
First run 

```bash
g++ -std=c++11 main.cpp ./Model/SystemModel.cpp ./Libs/Config.cpp ./Controllers/HomepageController.cpp -o Group4_program.exe
```
to create file .exe, then run

```bash
./Group4_program.exe
```
