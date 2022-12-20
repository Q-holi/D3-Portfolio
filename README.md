# D3D11-Portfolio

**개발환경[IDE] - Integrated Development Environment**

 1. visual studio 2019
 2. C++

**라이브러리[libraries]**

 1. STL: Standard Template Library
 2. DirectX - d3d11.h
 3. Imgui - Docking.ver
 4. DirectXTk - SimpleMath



| Development | Preview |
|:---:|:---:|
|**Scaling Mechanic**|![Superliminal scaling mechanic](https://user-images.githubusercontent.com/32233160/208629664-16cc06dc-be21-44ba-bdb4-ba0d1eddb429.gif)|
| 설명[Description]|게임 **Superliminal** 의 영감을 받아 원근감을 주는 scaling 구현  |
|**ObjectPicking**| ![ObjectPicking](https://user-images.githubusercontent.com/32233160/208630023-6d29e952-b113-4247-8c84-7c6d63bc3122.gif)|
| 설명[Description]|사용자 **어느 Object**를 지목했는가 **Hierarchy/Detail** 즉시 열람 |
| **Assimp<br>ModelImport** | ![AssimpModelImport](https://user-images.githubusercontent.com/32233160/208655224-3992654d-83f9-4fa1-9694-dc6e655f20c3.gif)|
| 설명[Description]|**Bone Animation / Skinned Mesh** 적용하여 Model 불러오기|
| **Assimp<br>AnimationImport** | ![AssimpAnimationImport](https://user-images.githubusercontent.com/32233160/208655384-09edaecf-25fe-4691-ac7c-a2d91459226c.gif)|
| 설명[Description]|여러 Animation을 리스트화 하여 간편하게 Import 및 실행|
| **Poftfolio Edtier** | ![Portfolio-Editer](https://user-images.githubusercontent.com/32233160/208633415-90088c53-348c-4846-9f85-9ae53bc3356e.png) |
| 설명[Description]|ImGui를 활용하여 필요한 Editer 구현|
| **CollisionDetector** | ![CollisionDetector](https://user-images.githubusercontent.com/32233160/208656509-d833ef65-27c8-47d5-9e52-c84042bc8a36.png) |
| **ImGui String** | ![AssimpAnimationImport](https://user-images.githubusercontent.com/32233160/208657718-a379d767-4640-4b95-8f7f-fc594b745f6d.png)|

**실패한 부분**
 1. nvidia physx 불러오기 
 > 다른 Open physic도 사용 해보기 
 2. CollisionResolver 적용
   > Sequential Impulse Solver 기반 충돌 조사 및 적용
 3. CollisionDetector 모든 오브젝트 적용
  > Separating Axis Theorem 를 이용한 다양한 충돌 감지 조사 및 적용

