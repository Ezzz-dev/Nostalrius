local closedDoors = {
	[1628] = 1630,
	[1629] = 1628,
	[1631] = 1633,
	[1632] = 1631,
	[1650] = 1652,
	[1651] = 1650,
	[1653] = 1655,
	[1654] = 1653,
	[1668] = 1670,
	[1669] = 1668,
	[1671] = 1673,
	[1672] = 1671,
	[1682] = 1684,
	[1683] = 1682,
	[1691] = 1693,
	[1692] = 1691,
}

local openDoors = {
	[1630] = 1628,
	[1633] = 1631,
	[1652] = 1650,
	[1655] = 1653,
	[1670] = 1668,
	[1673] = 1671,
	[1684] = 1682,
	[1693] = 1691,
}

function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	local door = closedDoors[target:getId()]
	if not door then
		door = openDoors[target:getId()]
	end
	
	if not door then
		return false
	end
	
	local keyNumber = item:getAttribute(ITEM_ATTRIBUTE_KEYNUMBER)
	local keyHoleNumber = target:getAttribute(ITEM_ATTRIBUTE_KEYHOLENUMBER)
	
	if keyHoleNumber == 0 or keyNumber ~= keyHoleNumber then
		player:sendCancelMessage("The key does not match.")
		return true
	end
	
	target:transform(door)
	target:decay()
	return true
end
