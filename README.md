# UnrealEngine_Explore
Explore UnrealEngine in CPP(main) / Blueprint(co)

### Editor
 - New Cpp classes: Switch to ```C++ Classes```, right click to create new cpp class.
 - Delete Cpp classes: Delete local ```.cpp && .h``` files, then delete binary files and restart editor (UE will rebuild the project). Then, the unwanted cpp classes are removed from the editor.


### Coding
 - Reflection System in UnrealEngine [→](https://www.unrealengine.com/en-US/blog/unreal-property-system-reflection?sessionInvalidated=true): By ```#include "FileName.generated.h"```, You can now use ```UENUM(), UCLASS(), USTRUCT(), UFUNCTION(), UPROPERTY(), ...``` to annotate different types and member variables in the header.
 	- ```UPROPERTY()``` [→](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/GameplayArchitecture/Properties/)
 	- ```UFUNCTION()``` [→](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/GameplayArchitecture/Functions/)

 - Coding Standard [→](https://docs.unrealengine.com/5.0/en-US/epic-cplusplus-coding-standardblueprint-debugging-in-unreal-engine/)

 - Forward Declaration: The standard way to declare a complex class, which indicates to additionally include other header files, in the current header file is to use __Forward Declaration__, which intuitively tells the compiler _"Currently I cannot give you the definition, but I promise I will give you later."_. This is because, if we do not use forward declaration and __do not include__ the extra header files, then the compiler will have no clue of what those types are, while if we do not use forward declaration and __do include__ the extra header files, then it will introduce the hazard of circular dependency. In other word, using forward declaration is the only secure way to solve this situtation.

 - Game Flow: Despite different play mode (Editor Mode / Standalone Mode), a coarse game flow can be concluded as follow. ```UWorld::BeginPlay``` is first called which starts the gameplay and correctifies the state of game mode [→](https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/Engine/UWorld/BeginPlay/). ```AGameMode::StartPlay``` and ```AGameMode::StartMatch``` is then called which spawns actors and triggers the actors' ```BeginPlay```. (For more details, please refer to [→](https://www.brightdevelopers.com/unreal-engine-4-game-flow-actor-lifecycle-overview/))
   - Therefore, always spawn actors in ```BeginPlay``` rather than the constructor, simply because during the constructor stage, ```UWorld``` is probably not prepared.

### API
 - Physics: The majority API of Physics is defined in ```UPrimitiveComponent``` [→](https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/). 
   - Note that when simulating physics, UE4 __always__ uses simple collision rather than complex collision.