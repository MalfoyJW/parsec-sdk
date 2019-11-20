using ParsecUnity;
using Rewired;
using UnityEngine;

class PlayerMovement : MonoBehaviour
{
    private bool automatic = false;
    public float speed = 5.0f;
    public int player = 1;
    [HideInInspector] private Rewired.Player m_re_player;


    private void Start()
    {
    }

    public void initReInput(CustomController controller, CustomController keyboard, CustomController mouse)
    {
        m_re_player = Rewired.ReInput.players.GetPlayer(player);
        if (player == 0)
        {
            m_re_player.controllers.AddController(Rewired.ReInput.controllers.Joysticks[0], true);
            m_re_player.controllers.hasKeyboard = true;
        }
        else
        {
            if (controller != null)
                m_re_player.controllers.AddController(controller, true);
            if (keyboard != null)
                m_re_player.controllers.AddController(keyboard, true);
            if (mouse != null)
                m_re_player.controllers.AddController(mouse, true);
        }
    }

    private void Update()
    {
        Vector3 moveVector = new Vector3(0, 0);
        moveVector.x = m_re_player.GetAxis("MoveLeftRight");
        moveVector.y = m_re_player.GetAxis("MoveUpDown");
        
        if (m_re_player.GetButtonDown("AutomaticMoving"))
        {
            automatic = !automatic;
        }
        if (automatic)
        {
            moveVector.x = -1;
        }


        transform.Translate(new Vector3(moveVector.x * 30.0f * Time.deltaTime, moveVector.y * 30.0f * Time.deltaTime, 0));

        Vector3 position = this.transform.position;
        if (position.x < -13.5)
        {
            position.x = 13.5f;
            this.transform.position = position;
        }
        else if (position.x > 13.5)
        {
            position.x = -13.5f;
            this.transform.position = position;
        }
        if (position.y < -8f)
        {
            position.y = 8f;
            this.transform.position = position;
        }
        else if (position.y > 8f)
        {
            position.y = -8f;
            this.transform.position = position;
        }
    }
}