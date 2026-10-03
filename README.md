# Small Facebook 🚀

A high-performance, modular C++ object-oriented backend application that simulates core social media functionalities inspired by Facebook. The project models complex user relationships, social interactions, media publishing, search indexing, and administrative account controls using Clean Architecture principles and Modern C++ standards.

---

## 📝 Description

**Small Facebook** is a system design project aimed at modeling a social networking platform from scratch using pure C++. 

Instead of relying on heavy external database management systems, this project implements a low-latency, **In-Memory Graph Data Structure** to represent complex social networks.

The system is designed with strict adherence to **Object-Oriented Programming (OOP)**, **SOLID principles**, and memory safety using smart pointers (`std::shared_ptr`), providing an enterprise-grade architecture suitable for technical review and system design case studies.

---

## ✨ Key Features

- **Recommendation Engine:** Real-time graph algorithm prioritizing member suggestions based on mutual connection counts.
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
```

### 2. "People You May Know" Graph Topology 

The recommendation algorithm traverses the target user's direct friends (Level 1) to evaluate their friends (Level 2). Mutual connection intersections are aggregated to rank recommendations.

```mermaid
graph LR
    Target[Target Member: Ahmed] <-->|Direct Connection| L1_A(Mona - Level 1)
    Target <-->|Direct Connection| L1_B(Ali - Level 1)
    
    L1_A <-->|Connection| L2_A(Sara - Level 2)
    L1_A <-->|Mutual Path 1| Rec((Omar - Suggested Candidate))
    L1_B <-->|Mutual Path 2| Rec
    
    style Rec fill:#2b82c5,color:#fff,stroke:#1a4971,stroke-width:2px
```
###3. Connection Suggestion Execution Flow
```mermaid
sequenceDiagram
    autonumber
    actor User as Ahmed (Member)
    participant M as Member Object
    participant Graph as In-Memory Network Graph
    
    User->>M: searchMemberSuggestions()
    M->>Graph: getMemberConnectionsById(Ahmed_ID)
    Graph-->>M: [Mona, Ali] (Level 1 Connections)
    
    loop For each Level 1 Member
        M->>Graph: getMemberConnectionsById(Mona_ID)
        Graph-->>M: [Sara, Omar] (Level 2 Connections)
        M->>M: findMemberSuggestion(Omar) -> Increment Frequency Count
    end
    
    M-->>User: Ranked Vector of Candidates [(Omar, count: 2), (Sara, count: 1)]
```
4. High-Level Layered Architecture
```mermaid
graph TD
    subgraph Client Layer
        AdminRole[Admin Operations Module]
        MemberRole[Member Operations Module]
    end

    subgraph Core Domain Layer
        Account[Account & Person Base]
        Entities[Page, Group, Post, Message]
    end

    subgraph In-Memory Data Layer
        Registry[Member Registry Map]
        GraphDB[(In-Memory Network Graph)]
        SearchEngine[Search Index Engine]
    end

    AdminRole --> Account
    MemberRole --> Entities
    MemberRole --> GraphDB
    MemberRole --> SearchEngine
    Registry --> Account
```
📂 Directory Structure
```text
.
├── Account.hpp                     # Abstract base class for security/credentials
├── AccountStatus.hpp               # Account state enumeration
├── Address.hpp                     # Value object for locations
├── Admin.hpp                       # Administrative system operations
├── Comment.hpp                     # Post comments entity
├── ConnectionInvitation.hpp        # Connection invitation model & states
├── ConnectionInvitationStatus.hpp  # Status enum for connection requests
├── ForwardDeclarations.hpp         # System-wide type forward declarations
├── Group.hpp                       # Member communities entity
├── Member.hpp                      # Main user entity & recommendation logic
├── Message.hpp                     # Direct messaging entity
├── Page.hpp                        # Public social pages entity
├── Person.hpp                      # Personal details domain class
├── Post.hpp                        # Content publishing model
├── Profile.hpp                     # Member bio, work experience & history
├── Recommendation.hpp              # Page recommendation reviews
├── Search.hpp                      # Abstract search interface
├── SearchIndex.hpp                 # In-memory search index implementation
├── Work.hpp                        # Career profile entry
├── main.cpp                        # Main application entry point and demonstration
├── test.cpp                        # Test scenarios for core system functionality
└── README.md                       # Project documentation
```
🛠 Building & Running Small Facebook
Prerequisites

    A C++17 compatible compiler (g++ 7+, clang++ 5+, or MSVC 2017+)

Direct Terminal Compilation
```
    g++ -std=c++17 main.cpp -I. -o small_facebook
    ./small_facebook
