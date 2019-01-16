function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 33176, y = 32880, z = 11},2570) and Game.isItemThere ({x = 33175, y = 32884, z = 11},2570) and Game.isItemThere ({x = 33176, y = 32889, z = 11},2570) and Game.isItemThere ({x = 33182, y = 32880, z = 11},2570) and Game.isItemThere ({x = 33183, y = 32884, z = 11},2570) and Game.isItemThere ({x = 33181, y = 32889, z = 11}, 2570) then
		doRelocate(item:getPosition(),{x = 33198, y = 32885, z = 11})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33198, y = 32885, z = 11}, 11)
		Game.transformItemOnMap({x = 33176, y = 32880, z = 11}, 2570, 2569)
		Game.transformItemOnMap({x = 33175, y = 32884, z = 11}, 2570, 2569)
		Game.transformItemOnMap({x = 33176, y = 32889, z = 11}, 2570, 2569)
		Game.transformItemOnMap({x = 33182, y = 32880, z = 11}, 2570, 2569)
		Game.transformItemOnMap({x = 33183, y = 32884, z = 11}, 2570, 2569)
		Game.transformItemOnMap({x = 33181, y = 32889, z = 11}, 2570, 2569)
	else
		doRelocate(item:getPosition(),{x = 33179, y = 32889, z = 11})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33179, y = 32889, z = 11}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33179, y = 32889, z = 11})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33179, y = 32889, z = 11}, 11)
end
