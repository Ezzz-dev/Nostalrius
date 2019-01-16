function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32479, y = 31920, z = 07},3696) and Game.isItemThere ({x = 32478, y = 31920, z = 07},3696) and Game.isItemThere ({x = 32478, y = 31902, z = 07}, 1791) then
		Game.transformItemOnMap({x = 32478, y = 31902, z = 07}, 1791, 1947)
		Game.sendMagicEffect({x = 32478, y = 31902, z = 07}, 3)
	end
end
