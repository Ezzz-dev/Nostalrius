function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32167, y = 32438, z = 09})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 32167, y = 32438, z = 09}, 15)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32167, y = 32438, z = 09})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 32167, y = 32438, z = 09}, 15)
end
