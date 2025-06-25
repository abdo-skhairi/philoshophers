# philosophers 🍽️

![Preview](https://github.com/abdo-skhairi/philoshophers/blob/main/Pholosophers.png)
A concurrency-based simulation of the famous Dining Philosophers Problem, implemented in C using threads and mutexes.

[🔗 GitHub Repository](https://github.com/abdo-skhairi/philoshophers.git)

---

## 🧠 About The Project

**Philosophers** is one of the 42 Network projects aimed at tackling the well-known synchronization problem, *Dining Philosophers*. It focuses on **multithreading**, **mutexes**, **deadlock prevention**, and race condition mitigation in C programming.  

The project’s main goal is to teach students how to:  

* Use **POSIX threads (`pthread`)**

* Manage shared resources with **mutexes**

* Implement safe timing and thread behavior 

* Prevent **deadlocks** and ensure **data consistency**

---

## 📦 Installation

### Requirements

* GCC or Clang
* Make
* Unix-like environment (Linux/macOS)

### Setup

```bash
git clone https://github.com/abdo-skhairi/philoshophers.git
cd philoshophers
make
```


## 🧪 How It Operates

Each philosopher functions as a thread and performs the following cyclical tasks:

1. **Thinking 🤔**
  
2. **Taking forks 🍴**
  
3. **Eating 🍝**
  
4. **Sleeping 😴**   

There is a limit to how long a philosopher can go without eating; otherwise they ‘die’. Under certain conditions, the simulation either ends upon one ‘death,’ or when all participants reach a specified number of required meals.

---

## ⚙️ Features  

* State logging, monitored by threads for security

* Precision time marking via `gettimeofday`

* Accurate pause utilizing custom `usleep`

* Strategy for prevention of deadlocks

* Optional: tracking for count during additional consumption

## 📬 Contact Me

- 📧 **Email:** skhairi.abderahmane@gmail.com  
- 📸 **Instagram:** [@abdo.skh](https://instagram.com/abdo.skh)
