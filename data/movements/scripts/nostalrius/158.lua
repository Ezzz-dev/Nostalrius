function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32584, y = 32465, z = 09},2567) and Game.isItemThere ({x = 32583, y = 32482, z = 09},2567) and Game.isItemThere ({x = 32610, y = 32523, z = 09},2567) and Game.isItemThere ({x = 32619, y = 32523, z = 09},2567) and Game.isItemThere ({x = 32647, y = 32483, z = 09},2567) and Game.isItemThere ({x = 32645, y = 32465, z = 09}, 2567) then 
		doRelocate({x = 32615, y = 32484, z = 09},{x = 32615, y = 32485, z = 10})
		Game.sendMagicEffect({x = 32615, y = 32485, z = 10}, 11)
	else
		doRelocate({x = 32615, y = 32484, z = 09},{x = 32615, y = 32483, z = 09})
		Game.sendMagicEffect({x = 32615, y = 32483, z = 09}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32615, y = 32484, z = 09},{x = 32615, y = 32483, z = 09})
	Game.sendMagicEffect({x = 32615, y = 32483, z = 09}, 11)
end