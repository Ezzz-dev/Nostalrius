function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 33028, y = 32588, z = 13},2570) and Game.isItemThere ({x = 33006, y = 32563, z = 13},2570) and Game.isItemThere ({x = 33027, y = 32530, z = 13},2570) and Game.isItemThere ({x = 33036, y = 32507, z = 13},2570) and Game.isItemThere ({x = 33055, y = 32487, z = 13},2570) and Game.isItemThere ({x = 33077, y = 32507, z = 13},2570) and Game.isItemThere ({x = 33089, y = 32514, z = 13},2570) and Game.isItemThere ({x = 33104, y = 32514, z = 13},2570) and Game.isItemThere ({x = 33130, y = 32489, z = 13},2570) and Game.isItemThere ({x = 33147, y = 32524, z = 13},2570) and Game.isItemThere ({x = 33123, y = 32599, z = 13}, 2570) then 
		doRelocate(item:getPosition(),{x = 33083, y = 32571, z = 14})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33083, y = 32571, z = 14}, 11)
	else
		doRelocate(item:getPosition(),{x = 33083, y = 32568, z = 13})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33083, y = 32568, z = 13}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33083, y = 32568, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33083, y = 32568, z = 13}, 11)
end
