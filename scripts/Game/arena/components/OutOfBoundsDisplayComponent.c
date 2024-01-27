[EntityEditorProps(category: "GunGame/Components", description: "Out of bounds display")]
class OutOfBoundsDisplayComponentClass: GameComponentClass
{
}

class OutOfBoundsDisplayComponent: GameComponent
{
	protected ref Widget outOfBoundsWidget = GetGame().GetWorkspace().CreateWidgets("{993CBCD0B922DBF5}UI/layouts/RUGG_OutOfBoundsWarning.layout");
	
	void OutOfBoundsDisplayComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		outOfBoundsWidget.SetVisible(false);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void rpcSetWidgetDisplay(bool visible)
	{
		outOfBoundsWidget.SetVisible(visible);
	}
	
	void setWidgetDisplay(bool visible)
	{
		Rpc(rpcSetWidgetDisplay, visible);
	}
}