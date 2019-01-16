function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32255, y = 31837, z = 09},2026) then 
		Game.sendMagicEffect({x = 32255, y = 31837, z = 09}, 3)
		Game.removeItemOnMap({x = 32255, y = 31837, z = 09}, 2026)
		doRelocate({x = 32255, y = 31837, z = 10},{x = 32255, y = 31837, z = 09})
	end
end
