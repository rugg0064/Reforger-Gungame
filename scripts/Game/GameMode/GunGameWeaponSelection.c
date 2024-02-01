[BaseContainerProps(configRoot: true), BaseContainerCustomTitleField("GunGameWeaponSelection")]
class GunGameWeaponSelection
{
	[Attribute("", UIWidgets.ResourceNamePicker, params: "")]
	ResourceName resourceName;
	
	[Attribute("GUN/GRENADE/PISTOL", UIWidgets.EditBox, params: "et")]
	string type;
	
	ResourceName getResourceName()
	{
		return resourceName;
	}
	
	string getType()
	{
		return type;
	}
	
}