function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32478, y = 31902, z = 07}, 1947) then 
		Game.transformItemOnMap({x = 32478, y = 31902, z = 07}, 1947, 1791)
		Game.sendMagicEffect({x = 32478, y = 31902, z = 07}, 3)
	end
end
