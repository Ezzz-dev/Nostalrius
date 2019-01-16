function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32595, y = 32744, z = 06})
		creature:getPlayer():setTown(Town("Port Hope"))
		Game.sendMagicEffect({x = 32595, y = 32744, z = 06}, 13)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32595, y = 32744, z = 06})
	Game.sendMagicEffect({x = 32595, y = 32744, z = 06}, 14)
end
