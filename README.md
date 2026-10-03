# Small Facebook 🚀

A high-performance, modular C++17 object-oriented backend application that simulates core social media functionalities inspired by Facebook. The project models complex user relationships, social interactions, media publishing, search indexing, and administrative account controls using Clean Architecture principles and Modern C++ standards.

---

## 📝 Description

**Small Facebook** is a system design project aimed at modeling a large-scale social networking platform from scratch using pure C++. 

Instead of relying on heavy external database management systems, this project implements a low-latency, **In-Memory Graph Data Structure** to represent complex social networks. It features a custom **2-Level Breadth-First Search (BFS)** algorithm that analyzes mutual connection paths to deliver highly accurate friend recommendations—similar to Facebook's "People You May Know" algorithm.

The system is designed with strict adherence to **Object-Oriented Programming (OOP)**, **SOLID principles**, and memory safety using smart pointers (`std::shared_ptr`), providing an enterprise-grade architecture suitable for technical review and system design case studies.

---

## ✨ Key Features

- **2-Level BFS Recommendation Engine:** Real-time graph algorithm prioritizing member suggestions based on mutual connection counts.
- **In-Memory Network Graph:** Ultra-fast $O(1)$ relationship lookups via `std::unordered_map` and `std::unordered_set`.
- **Role-Based Access Control:** Administrative oversight (`Admin`) capable of enforcing security actions (blocking/unblocking accounts, enabling/disabling pages).
- **Search Engine Indexing:** Decoupled search interface (`Search`) providing fast lookups for members, pages, groups, and posts.
- **Smart Memory Management:** Automatic resource tracking using Modern C++ RAII and smart pointer wrappers to eliminate memory leaks.

---

## 📐 System Architecture & Diagrams

### 1. Class Diagram (Domain Model)

```mermaid
classDiagram
    class Account {
        <<Abstract>>
        -String id
        -String password
        -AccountStatus status
        +resetPassword(String newPassword) bool
    }

    class Person {
        <<Abstract>>
        -String name
        -Address address
        -String email
        -String phone
    }

    class Member {
        -int memberId
        -Profile profile
        -unordered_set~int~ memberConnections
        +addConnection(int friendId) void
        +searchMemberSuggestions() vector~pair~
    }

    class Admin {
        +blockUser(int memberId) bool
        +unblockUser(int memberId) bool
        +enablePage(Page& page) bool
        +disablePage(Page& page) bool
    }

    class Search {
        <<Interface>>
        +searchMember(String name)* vector
        +searchPage(String title)* vector
        +searchGroup(String name)* vector
        +searchPost(String word)* vector
    }

    class SearchIndex {
        -unordered_map memberNames
        -unordered_map pageTitles
        +addMember(shared_ptr~Member~) bool
        +searchMember(String name) vector
    }

    Account <|-- Person
    Person <|-- Member
    Person <|-- Admin
    Search <|.. SearchIndex
    Member "1" *-- "1" Profile
