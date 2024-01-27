[EntityEditorProps(category: "Arena", description: "Forces players in an enclosed area", color: "0 255 0 0")]
class RUGG_boundaryManagerEntityClass : SCR_CaptureAreaClass
{
}

class RUGG_boundaryManagerEntity : SCR_CaptureArea
{
	[Attribute(defvalue: "5", uiwidget: UIWidgets.Slider, desc: "Out of bounds grace period (in seconds)", params: "1 30 1")]
	protected float outOfBoundsGracePeriodSeconds;
	
	protected ref map<SCR_ChimeraCharacter, ref float> outOfBoundsPlayers = new map<SCR_ChimeraCharacter, ref float>;

	protected override void OnCharacterEntered(Faction faction, SCR_ChimeraCharacter character)
    {
        super.OnCharacterEntered(faction, character);
		outOfBoundsPlayers.Remove(character);
		setCharacterDisplay(character, false);
    }
	
	protected override void OnCharacterExit(Faction faction, SCR_ChimeraCharacter character)
    {
        super.OnCharacterExit(faction, character);
		if(character.GetDamageManager().GetHealth() <= 0)
		{
			return;
		}
		setCharacterDisplay(character, true);
		outOfBoundsPlayers.Insert(character, outOfBoundsGracePeriodSeconds);
    }
	
	private void setCharacterDisplay(SCR_ChimeraCharacter character, bool visible)
	{
		OutOfBoundsDisplayComponent component = OutOfBoundsDisplayComponent.Cast(character.FindComponent(OutOfBoundsDisplayComponent));
		component.setWidgetDisplay(visible);
	}
	
	
	protected override void EOnFrame(IEntity owner, float timeSlice)
	{
		foreach(SCR_ChimeraCharacter character, float timeLeft : outOfBoundsPlayers)
		{
			timeLeft -= timeSlice;
			outOfBoundsPlayers.Set(character, timeLeft);
			if(timeLeft < 0)
			{
				character.GetDamageManager().Kill(Instigator.CreateInstigator(this));
				outOfBoundsPlayers.Remove(character);
				setCharacterDisplay(character, false);
			}
		}
	}
	
	protected override void OnInit(IEntity owner)
	{
		super.OnInit(owner);
	}
	
	void RUGG_boundaryManagerEntity(IEntitySource src, IEntity parent)
	{
		//SetFlags(EntityFlags.ACTIVE | EntityFlags.NO_LINK, false);
		//SetEventMask( EntityEvent.FRAME);
	}
}