#include "SceneParent.h"
#include "NetworkClient.h"
#include "NetworkServer.h"





void SceneParent::load()
{
}

void SceneParent::start()
{
}

void SceneParent::update()
{


    //---------Gère le online et tente de se connecter
    if (isOnline())
    {
        // Try to establish connection
        if (!connectionEstablished)
        {
            connectionEstablished = networkAgent->establishConnection();
            if (connectionEstablished)
                handleConnectionEstablished();
            return;
        }
    }

    onUpdate();


    //------Update de chaque objet
    for (auto& gameObjectPair : gameObjectMap)
    {
        Actor* gameObject = gameObjectPair.second;	//On stoque le game object 

        if (gameObjectPair.second->isActive)
        {
            gameObject->Update();
        }

        //---------  Gère le online 
        if (isOnline())
        {
            //Si on est serveur on envoie toutes les données
            if (sceneMode == SceneMode::OnlineServer)
            {
                //On envoie un packet avec les données du game object
                
                //Packet* packet = new Packet(gameObject);
                //networkAgent->sendPacket(packet);
            }

            //Si on est client on n'envoie que les données des objets update from client
            else if (sceneMode == SceneMode::OnlineClient)
            {
                //Si l'objet 
                if (gameObject->updateFromClient)
                {
                    //Packet* packet = new Packet(gameObject);
                    //networkAgent->sendPacket(packet);
                }
            }
        }
    }


}

void SceneParent::draw()
{
}

void SceneParent::drawUi()
{
}

void SceneParent::close()
{
    for (auto& gameObjectPair : gameObjectMap)
    {
        gameObjectPair.second->Destroy();
        delete gameObjectPair.second;
    }
    gameObjectMap.clear();
    destroyNetworkAgent();
}

void SceneParent::onUpdate()
{
}

CameraActor* SceneParent::getCamera()
{
    return &cam;
}

void SceneParent::setSceneMode(const SceneMode sceneModeP)
{
    sceneMode = sceneModeP;

    // Set l'agent en client et en serveur
    switch (sceneMode)
    {
    case SceneMode::OnlineClient:
        networkAgent = new NetworkClient();
        break;
    case SceneMode::OnlineServer:
        networkAgent = new NetworkServer();
        break;
    }

    if (isOnline())
    {
        // Threading
        sem = SDL_CreateSemaphore(1);
        thread = SDL_CreateThread(recvPacketThread, "defu", this);
        SDL_DetachThread(thread);
    }
}

void SceneParent::destroyNetworkAgent()
{
    if (alreadyDestroyed)
        return;
    if (isOnline())
    {
        if (sem)

        {
            SDL_DestroySemaphore(sem);
            sem = nullptr;
        }
        networkAgent->destroy();
        alreadyDestroyed = true;
    }
}
void SceneParent::disconnect()
{
    onDisconnect();
    disconnected = true;
}
bool SceneParent::isOnline() const
{
    return sceneMode == SceneMode::OnlineClient
        || sceneMode == SceneMode::OnlineServer;

}

/// <summary>
/// Pour gérer la récéption des paquet 
/// </summary>
/// <param name="packet"></param>
/// <returns></returns>
bool SceneParent::handlePacket(Packet* packet)
{
    //Si y'a pas de paquet on ignore
    if (!packet)
        return false;


    Uint16 id = packet->id;	// stoque l'id du paquet

    //On va chercher dans la liste des objets de la scene l'objet que le paquet doit update
  //  GameObject* gameObject = gameObjectMap.at(id);	//Récupère le gameobject en fonction de l'id



    if (sceneMode == SceneMode::OnlineServer)
    {
        //Le serveur va reçevoir le paquet 
        /*
        if (gameObject->updateFromClient)	//Si l'objet s'update à partir des infos du client
            gameObject->transform.position = packet->position;	//Bouge l'objet en fonction de des données du paquet
        */
    }
    else if (sceneMode == SceneMode::OnlineClient)
    {
        //Si on est le client fait bouger l'autre paddle 
        /*
        if (!gameObject->updateFromClient)	//Si l'objet ne s'update pas
            gameObject->transform.position = packet->position;

        //Get le componenet movement de l'objet à update
        CompMove* move = gameObject->getComponent<CompMove>();
        if (move)
            move->setDirection(packet->direction);
        */
    }
    return true;
}


int recvPacketThread(void* data)
{
    SceneParent* scene = (SceneParent*)data;
    Packet* packet = nullptr;
    bool valid = false;
    while (true)
    {
        if (scene->disconnected)
            break;
        if (!scene->connectionEstablished)
            continue;
        // Receive data
        packet = scene->networkAgent->recvPacket();
        SDL_SemWait(scene->sem);
        if (!packet)
        {
            scene->disconnect();
            SDL_SemPost(scene->sem);
            break;
        }
        valid = scene->handlePacket(packet);
        if (!valid)
        {
            scene->disconnect();
            SDL_SemPost(scene->sem);
            break;
        }
        SDL_SemPost(scene->sem);
    }
    return 0;
}