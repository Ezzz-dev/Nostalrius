local verticalDoors = {
	[1643] = 1642,
	[1647] = 1646,
	[1661] = 1660,
	[1665] = 1664,
	[1675] = 1674, 
	[1679] = 1678, 
	[1697] = 1696, 
	[1699] = 1698,
}

local horizontalDoors = {
	[1645] = 1644, 
	[1649] = 1648, 
	[1663] = 1662,
	[1667] = 1666, 
	[1677] = 1676, 
	[1681] = 1680,
	[1688] = 1687,
	[1690] = 1689,
}

function onStepOut(creature, item, fromPosition, toPosition)
	local door = verticalDoors[item:getId()]
	if door then
		doRelocate(item:getPosition(), item:getPosition():moveRel(1, 0, 0))
		item:transform(door)
		item:decay()
		return true
	end
	
	door = horizontalDoors[item:getId()]
	if door then
		doRelocate(item:getPosition(), item:getPosition():moveRel(0, 1, 0))
		item:transform(door)
		item:decay()
		return true
	end
end