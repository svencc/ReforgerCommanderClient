class Menu: SCR_InfoDisplay
{
    // private ButtonWidget TestButton;
    override event void OnStartDraw(IEntity owner)
    {
		Print("Menu -> SCR_InfoDisplay ON DRAW");
        super.OnStartDraw(owner);
        //if (!TestButton) TestButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("TestH"));
    }
}