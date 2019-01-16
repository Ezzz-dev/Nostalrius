function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32266, y = 31892, z = 12}, 394) then 
		Game.transformItemOnMap({x = 32266, y = 31892, z = 12}, 394, 372)
	end
end
