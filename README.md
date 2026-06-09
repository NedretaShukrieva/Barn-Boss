# Barn-Boss
Object-oriented programming project C++

# BarnBoss 🌾

## Description

A console-based farm management simulation game built with object-oriented C++. Players manage their own farm, trade on a shared market, and complete tasks to earn points and climb the leaderboard.

## Features

- Multi-user system with authentication
- Farm management (plant crops, raise animals, harvest)
- Shared marketplace for buying and selling
- Task board with rewards
- Global scoreboard
- Save/load game state

## Commands

### Without a logged-in user
| Command | Description |
|---|---|
| `register <username> <password> <type>` | Register a new user (Player/MarketManager/TaskManager) |
| `login <username> <password>` | Log in |
| `exit` | Save and quit |

### Player commands
| Command | Description |
|---|---|
| `buyItem <id> <quantity>` | Buy from market |
| `sellItem <id> <quantity>` | Sell to market |
| `sowPlant <id>` | Plant a seed |
| `addAnimal <id>` | Add an animal |
| `harvest` | Collect produce |
| `completeTask <id>` | Complete a task |
| `expandCropland` | Expand crop slots |
| `expandFarmland` | Expand animal slots |
| `checkBarn` | View inventory |
| `checkFarm` | View farm status |
| `checkBalance` | View balance |
| `checkScore` | View score |
| `showTaskBoard` | View tasks |
| `openMarketCatalog` | View market |
| `showScoreboard` | View rankings |

### MarketManager commands
| Command | Description |
|---|---|
| `openMarketCatalog` | View market |
| `restock <id> <quantity>` | Restock a product |
| `changePrice <id> <newPrice>` | Change a product's price |

### TaskManager commands
| Command | Description |
|---|---|
| `showTasks` | View all tasks |
| `addTask <product> <quantity> <rewardBalance> <rewardScore>` | Add a task |
| `removeTask <id>` | Remove a task |

## Products
| ID | Product | Price |
|---|---|---|
| 1 | Wheat Seed | 10 |
| 2 | Corn Seed | 15 |
| 3 | Chicken | 25 |
| 4 | Cow | 50 |
| 5 | Wheat | 15 |
| 6 | Corn | 20 |
| 7 | Egg | 30 |
| 8 | Milk | 60 |

## Project Structure

```bash
BarnBoss/
├── User/
│   ├── User.h / User.cpp
│   ├── UserValidator.h / UserValidator.cpp
│   ├── UserFactory.h / UserFactory.cpp
│   ├── Player.h / Player.cpp
│   ├── TaskManager.h / TaskManager.cpp
│   └── MarketManager.h / MarketManager.cpp
│
├── Farm/
│   ├── Farm.h / Farm.cpp
│   ├── FarmObject.h / FarmObject.cpp
│   ├── Plantable.h / Plantable.cpp
│   └── Animal.h / Animal.cpp
│
├── Market/
│   ├── Market.h / Market.cpp
│   └── MarketItem.h / MarketItem.cpp
│
├── Taskboard/
│   ├── Taskboard.h / Taskboard.cpp
│   └── Task.h / Task.cpp
│
├── System/
│   ├── System.h / System.cpp
│
├── GameSerializer/
│   ├── GameSerializer.h / GameSerializer.cpp
│
├── Utils/
│   ├── Utils.h
│   └── Utils.cpp
│
├── GameException/
│   └── GameException.h

## Design Patterns Used
- **Factory** — `UserFactory` creates the correct user type
- **Single Responsibility** — each class handles one concern

## Technologies
- C++23
- Visual StudioSonnet 4.6 Low
