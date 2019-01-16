function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32104, y = 32082, z = 07}, 4597) then 
		Game.transformItemOnMap({x = 32104, y = 32082, z = 07}, 4597, 4615)
	end
end
